//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//

// Project includes
#include "cad_json_input.h"

namespace Kratos
{

    ///@name Python exposed Functions
    ///@{

    /// Adds all CAD geometries to the herin provided model_part.
    template<class TNodeType, class TEmbeddedNodeType>
    void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadModelPart(ModelPart& rModelPart)
    {
        ReadGeometryModelPart(mCadJsonParameters, rModelPart, mEchoLevel);
    }

    ///@}
    ///@name Static Functions
    ///@{

    /// Allows static access without own memory.
    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadGeometryModelPart(
        const Parameters& rCadJsonParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_ERROR_IF_NOT(rCadJsonParameters.Has("breps"))
            << "Missing \"breps\" section" << std::endl;

        ReadBreps(rCadJsonParameters["breps"], rModelPart, EchoLevel);
    }

    ///@}
    ///@name Read in Brep
    ///@{

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBreps(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        for (IndexType brep_index = 0; brep_index < rParameters.size(); brep_index++)
        {
            KRATOS_INFO_IF("ReadBreps", (EchoLevel > 0))
                << "Reading Brep \"" << GetIdOrName(rParameters[brep_index])
                << "\" - faces." << std::endl;

            ReadBrepFaces(rParameters[brep_index], rModelPart, EchoLevel);
        }

        for (IndexType brep_index = 0; brep_index < rParameters.size(); brep_index++)
        {
            KRATOS_INFO_IF("ReadBreps", (EchoLevel > 0))
                << "Reading Brep \"" << GetIdOrName(rParameters[brep_index])
                << "\" - edges." << std::endl;

            ReadBrepEdges(rParameters[brep_index], rModelPart, EchoLevel);
        }
    }

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBrepFaces(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        if (rParameters.Has("faces"))
        {
            ReadBrepSurfaces(rParameters["faces"], rModelPart, EchoLevel);
        }
    }

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBrepEdges(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        if (rParameters.Has("edges"))
        {
            ReadBrepCurveOnSurfaces(rParameters["edges"], rModelPart, EchoLevel);
        }
    }

    ///@}
    ///@name Read in Brep Geometries
    ///@{

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBrepSurfaces(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_ERROR_IF_NOT(rParameters.IsArray())
            << "\"faces\" section needs to be an array of BrepSurfaces." << std::endl;

        KRATOS_INFO_IF("ReadBrepSurfaces", EchoLevel > 2)
            << "Reading " << rParameters.size() << " BrepSurfaces..." << std::endl;

        for (IndexType brep_surface_i = 0; brep_surface_i < rParameters.size(); ++brep_surface_i)
        {
            ReadBrepSurface(rParameters[brep_surface_i], rModelPart, EchoLevel);
        }
    }

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBrepSurface(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_INFO_IF("ReadBrepSurface", (EchoLevel > 3))
            << "Reading BrepSurface \"" << GetIdOrName(rParameters) << "\"" << std::endl;

        KRATOS_ERROR_IF_NOT(HasIdOrName(rParameters))
            << "Missing 'brep_id' or 'brep_name' in brep face." << std::endl;

        KRATOS_ERROR_IF_NOT(rParameters.Has("surface"))
            << "Missing 'surface' in brep face." << std::endl;

        auto p_surface = ReadNurbsSurface<3, TNodeType>(
            rParameters["surface"], rModelPart, EchoLevel);

        bool is_trimmed = true;
        if (rParameters["surface"].Has("is_trimmed")) {
            is_trimmed = rParameters["surface"]["is_trimmed"].GetBool();
        }
        else {
            KRATOS_INFO_IF("ReadBrepSurface", (EchoLevel > 4))
                << "For BrepSurface \"" << GetIdOrName(rParameters) << "\""
                << "\", is_trimmed is not provided in the input."
                << " is_trimmed = true is considered." << std::endl;
        }

        if (rParameters.Has("boundary_loops"))
        {
            BrepCurveOnSurfaceLoopArrayType outer_loops, inner_loops;
            tie(outer_loops, inner_loops) =
                ReadBoundaryLoops(rParameters["boundary_loops"], p_surface, rModelPart, EchoLevel);

            auto p_brep_surface =
                Kratos::make_shared<BrepSurfaceType>(
                    p_surface,
                    outer_loops,
                    inner_loops,
                    is_trimmed);

            SetIdOrName<BrepSurfaceType>(rParameters, p_brep_surface);

            rModelPart.AddGeometry(p_brep_surface);
        }
        else
        {
            KRATOS_INFO_IF("ReadBrepSurface", (EchoLevel > 4))
                << "For BrepSurface \"" << GetIdOrName(rParameters) << "\""
                << "\", boundary_loops are not provided in the input."
                << " It will be considered as untrimmed." << std::endl;

            auto p_brep_surface =
                Kratos::make_shared<BrepSurfaceType>(
                    p_surface);

            SetIdOrName<BrepSurfaceType>(rParameters, p_brep_surface);

            rModelPart.AddGeometry(p_brep_surface);
        }
    }

    ///@name Read in Nurbs Geometries
    ///@{

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBrepCurveOnSurfaces(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_ERROR_IF_NOT(rParameters.IsArray())
            << "\"faces\" section needs to be an array of BrepSurfaces." << std::endl;

        KRATOS_INFO_IF("ReadBrepCurveOnSurfaces", EchoLevel > 2)
            << "Reading " << rParameters.size() << " BrepEdge..." << std::endl;

        for (IndexType i = 0; i < rParameters.size(); i++)
        {
            ReadBrepEdge(rParameters[i], rModelPart, EchoLevel);
        }
    }

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBrepEdge(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_ERROR_IF_NOT(HasIdOrName(rParameters))
            << "Missing 'brep_id' or 'brep_name' in brep edge" << std::endl;

        if (rParameters.Has("topology"))
        {
            if (rParameters["topology"].size() == 0)
            {
                KRATOS_ERROR << "BrepCurves are not yet enabled." << std::endl;
            }
            else if (rParameters["topology"].size() == 1)
            {
                ReadBrepEdgeBrepCurveOnSurface(rParameters, rModelPart, EchoLevel);
            }
            else { // More than one topology means that a coupling geometry is required.
                ReadCouplingGeometry(rParameters, rModelPart, EchoLevel);
            }
        }
    }

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadBrepEdgeBrepCurveOnSurface(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_INFO_IF("ReadBrepEdge", (EchoLevel > 3))
            << "Reading BrepEdge \"" << GetIdOrName(rParameters) << "\"" << std::endl;

        KRATOS_ERROR_IF_NOT(HasIdOrName(rParameters["topology"][0]))
            << "Missing 'brep_id' or 'brep_name' in topology" << std::endl;

        KRATOS_INFO_IF("ReadBrepEdge", (EchoLevel > 4))
            << "Getting trim: \"" << rParameters["topology"][0]["trim_index"].GetInt()
            << "\" from geometry: \"" << GetIdOrName(rParameters["topology"][0])
            << "\"." << std::endl;

        GeometryPointerType p_geometry = GetGeometry(rParameters["topology"][0], rModelPart);
        GeometryPointerType p_brep_trim =
            p_geometry->pGetGeometryPart(rParameters["topology"][0]["trim_index"].GetInt());

        auto p_brep_curve_on_surface
            = dynamic_pointer_cast<BrepCurveOnSurfaceType>(p_brep_trim);
        KRATOS_ERROR_IF(p_brep_curve_on_surface == nullptr)
            << "dynamic_cast from Geometry to BrepCurveOnSurface not successfull. Brep Id: "
            << GetIdOrName(rParameters["topology"][0]) << " and trim index: "
            << rParameters["topology"][0]["trim_index"].GetInt() << std::endl;

        bool relative_direction = true;
        if (rParameters["topology"][0].Has("trim_index")) {
            relative_direction = rParameters["topology"][0]["trim_index"].GetInt();
        }
        else {
            KRATOS_INFO_IF("ReadBrepEdge", (EchoLevel > 4))
                << "For trim: \"" << rParameters["topology"][0]["trim_index"].GetInt()
                << "\" from geometry: \"" << GetIdOrName(rParameters["topology"][0])
                << "\", no relative_direction is provided in the input." << std::endl;
        }

        auto p_nurbs_curve_on_surface = p_brep_curve_on_surface->pGetCurveOnSurface();

        auto p_bre_edge_brep_curve_on_surface = Kratos::make_shared<BrepCurveOnSurfaceType>(
            p_nurbs_curve_on_surface, relative_direction);

        SetIdOrName<BrepCurveOnSurfaceType>(rParameters, p_bre_edge_brep_curve_on_surface);

        rModelPart.AddGeometry(p_bre_edge_brep_curve_on_surface);
    }

    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadCouplingGeometry(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_INFO_IF("ReadCouplingGeometry", (EchoLevel > 3))
            << "Reading CouplingGeometry \"" << GetIdOrName(rParameters) << "\"" << std::endl;

        typename CouplingGeometryType::GeometryPointerVector geometry_vector;

        for (IndexType i = 0; i < rParameters["topology"].size(); i++)
        {
            KRATOS_ERROR_IF_NOT(HasIdOrName(rParameters["topology"][0]))
                << "Missing 'brep_id' or 'brep_name' in topology of Coupling - BrepEdge" << std::endl;

            auto p_geometry = GetGeometry(rParameters["topology"][i], rModelPart);

            geometry_vector.push_back(
                p_geometry->pGetGeometryPart(rParameters["topology"][i]["trim_index"].GetInt()));
        }

        auto p_coupling_geometry = Kratos::make_shared<CouplingGeometryType>(
            geometry_vector);

        SetIdOrName<CouplingGeometryType>(rParameters, p_coupling_geometry);

        rModelPart.AddGeometry(p_coupling_geometry);
    }

    ///@}
    ///@name Read in Control Points
    ///@{

    /// Reads the weights of all control points and provides them in a Vector.
    template<class TNodeType, class TEmbeddedNodeType>
    static Vector CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadControlPointWeightVector(
        const Parameters& rParameters,
        SizeType EchoLevel)
    {
        Vector control_point_weights = ZeroVector(rParameters.size());
        KRATOS_ERROR_IF(rParameters.size() == 0)
            << "Length of control point list is zero!" << std::endl;
        KRATOS_ERROR_IF(rParameters[0].size() != 4)
            << "Control points need to be provided in following structure: [[x, y, z, weight]] or [id, [x, y, z, weight]]"
            << "Size of inner vector incorrect!"
            << std::endl;

        SizeType number_of_entries = rParameters[0].size();
        for (IndexType cp_idx = 0; cp_idx < rParameters.size(); cp_idx++)
        {
            control_point_weights[cp_idx] = rParameters[cp_idx][number_of_entries - 1][3].GetDouble();
        }

        return control_point_weights;
    }

    /// Reads a Node<3>::Pointer-vector of control points.
    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadControlPointVector(
        PointerVector<Node<3>>& rControlPoints,
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_ERROR_IF_NOT(rParameters.IsArray())
            << "\"control_points\" section needs to be an array." << std::endl;

        KRATOS_INFO_IF("ReadControlPointVector", EchoLevel > 4)
            << "Reading " << rParameters.size() << " control points of type Node<3>." << std::endl;

        for (IndexType cp_idx = 0; cp_idx < rParameters.size(); cp_idx++)
        {
            rControlPoints.push_back(ReadNode(rParameters[cp_idx], rModelPart));
        }
    }

    /// Reads a Point::Pointer-vector of control points.
    template<class TNodeType, class TEmbeddedNodeType>
    static void CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadControlPointVector(
        PointerVector<Point>& rControlPoints,
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        KRATOS_ERROR_IF_NOT(rParameters.IsArray())
            << "\"control_points\" section needs to be an array." << std::endl;

        KRATOS_INFO_IF("ReadControlPointVector", EchoLevel > 4)
            << "Reading " << rParameters.size() << " control points of type Point." << std::endl;

        for (IndexType cp_idx = 0; cp_idx < rParameters.size(); cp_idx++)
        {
            rControlPoints.push_back(ReadPoint(rParameters[cp_idx]));
        }
    }

    ///@}
    ///@name Read in Nodes/ Points
    ///@{

    /* Reads, and returns a Pointer to Node<3>.
    * Input needs to be a Parameter object:
    * [id, [x, y, z, weight]]
    */
    template<class TNodeType, class TEmbeddedNodeType>
    static Node<3>::Pointer CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadNode(
        const Parameters& rParameters,
        ModelPart& rModelPart,
        SizeType EchoLevel)
    {
        SizeType number_of_entries = rParameters.size();
        KRATOS_ERROR_IF((number_of_entries != 2))
            << "Control points as Node<3> need to be provided in following structure: [id, [x, y, z, weight]]"
            << std::endl;

        IndexType id = rParameters[0].GetInt();
        Vector cp = rParameters[1].GetVector();

        return rModelPart.CreateNewNode(id, cp[0], cp[1], cp[2]);
    }

    /* Reads, and returns a Pointer to Point.
    * Input needs to be a Parameter object:
    * [[x, y, z, weight]] or [id, [x, y, z, weight]]
    */
    template<class TNodeType, class TEmbeddedNodeType>
    static Point::Pointer CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadPoint(
        const Parameters& rParameters,
        SizeType EchoLevel)
    {
        SizeType number_of_entries = rParameters.size();
        KRATOS_ERROR_IF((number_of_entries != 1) && (number_of_entries != 2))
            << "Control points as Point need to be provided in following structure: "
            << "[[x, y, z, weight]] or [id, [x, y, z, weight]]" << std::endl;

        Vector cp = rParameters[number_of_entries - 1].GetVector();

        return Kratos::make_shared<Point>(cp[0], cp[1], cp[2]);
    }

    ///@}
    ///@name Utility functions
    ///@{

    /// Returns the string of either the 'brep_id' or the 'brep_name'. Used for output massages.
    template<class TNodeType, class TEmbeddedNodeType>
    static std::string CadJsonInput<TNodeType, TEmbeddedNodeType>::GetIdOrName(
        const Parameters& rParameters)
    {
        if (rParameters.Has("brep_id")) {
            return std::to_string(rParameters["brep_id"].GetInt());
        }
        else if (rParameters.Has("brep_name")) {
            return rParameters["brep_name"].GetString();
        }
        else {
            return "no_id_assigned";
        }
    }

    /// Checks if one of the 'brep_id' or the 'brep_name' is provided.
    template<class TNodeType, class TEmbeddedNodeType>
    static bool CadJsonInput<TNodeType, TEmbeddedNodeType>::HasIdOrName(
        const Parameters& rParameters)
    {
        return (rParameters.Has("brep_id") || rParameters.Has("brep_name"));
    }

    /// Returns the geometry with either the 'brep_id' or the 'brep_name'.
    template<class TNodeType, class TEmbeddedNodeType>
    static typename Kratos::CadJsonInput<TNodeType, TEmbeddedNodeType>::GeometryType::Pointer
        CadJsonInput<TNodeType, TEmbeddedNodeType>::GetGeometry(
            const Parameters& rParameters,
            ModelPart& rModelPart)
    {
        if (rParameters.Has("brep_id")) {
            return rModelPart.pGetGeometry(rParameters["brep_id"].GetInt());
        }
        else { // if (rParameters["topology"][i].Has("brep_name"))
            return rModelPart.pGetGeometry(rParameters["brep_name"].GetString());
        }
    }

    /// Reads in a json formatted file and returns its KratosParameters instance.
    template<class TNodeType, class TEmbeddedNodeType>
    static Parameters CadJsonInput<TNodeType, TEmbeddedNodeType>::ReadParamatersFile(
        const std::string& rDataFileName,
        SizeType EchoLevel)
    {
        // Check if rDataFileName ends with ".cad.json" and add it if needed.
        std::string data_file_name = rDataFileName;
        if (rDataFileName.compare(rDataFileName.size() - 9, 9, ".cad.json") != 0) {
            data_file_name += ".cad.json";
        }

        KRATOS_INFO_IF("ReadParamatersFile", EchoLevel > 3)
            << "Reading file: \"" << data_file_name << "\"" << std::endl;

        std::ifstream cad_json_file;
        cad_json_file.open(data_file_name);

        // Convert std::ifstream into std::string
        std::string cad_json_string((std::istreambuf_iterator<char>(cad_json_file)),
            std::istreambuf_iterator<char>());

        cad_json_file.close();

        return Parameters(cad_json_string);
    }

    ///@}
}  // namespace Kratos.