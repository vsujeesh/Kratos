// KRATOS  __  __ _____ ____  _   _ ___ _   _  ____
//        |  \/  | ____/ ___|| | | |_ _| \ | |/ ___|
//        | |\/| |  _| \___ \| |_| || ||  \| | |  _
//        | |  | | |___ ___) |  _  || || |\  | |_| |
//        |_|  |_|_____|____/|_| |_|___|_| \_|\____| APPLICATION
//
//  License:		 BSD License
//                       license: MeshingApplication/license.txt
//
//  Main authors:    Vicente Mataix Ferrandiz
//

#if !defined(KRATOS_MMG_UTILITIES)
#define KRATOS_MMG_UTILITIES

// System includes

// External includes

// Project includes
#include "meshing_application.h"
#include "includes/key_hash.h"
#include "includes/model_part.h"
#include "includes/kratos_parameters.h"

// NOTE: The following contains the license of the MMG library
/* =============================================================================
**  Copyright (c) Bx INP/Inria/UBordeaux/UPMC, 2004- .
**
**  mmg is free software: you can redistribute it and/or modify it
**  under the terms of the GNU Lesser General Public License as published
**  by the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  mmg is distributed in the hope that it will be useful, but WITHOUT
**  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
**  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
**  License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License and of the GNU General Public License along with mmg (in
**  files COPYING.LESSER and COPYING). If not, see
**  <http://www.gnu.org/licenses/>. Please read their terms carefully and
**  use this copy of the mmg distribution only if you accept them.
** =============================================================================
*/

namespace Kratos
{
///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

    /// Index definition
    typedef std::size_t                                               IndexType;

    /// Size definition
    typedef std::size_t                                                SizeType;

    /// Index vector
    typedef std::vector<IndexType>                              IndexVectorType;

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/**
 * @class MmgUtilities
 * @ingroup MeshingApplication
 * @brief This class are different utilities that uses the MMG library
 * @details This class are different utilities that uses the MMG library
 * @author Vicente Mataix Ferrandiz
 */
template<MMGLibrary TMMGLibray>
class KRATOS_API(MESHING_APPLICATION) MmgUtilities
{
public:

    ///@name Type Definitions
    ///@{

    /// Pointer definition of MmgUtilities
    KRATOS_CLASS_POINTER_DEFINITION(MmgUtilities);

    /// Node definition
    typedef Node <3>                                                   NodeType;
    // Geometry definition
    typedef Geometry<NodeType>                                     GeometryType;

    /// Conditions array size
    static constexpr SizeType Dimension = (TMMGLibray == MMGLibrary::MMG2D) ? 2 : 3;

    /// Conditions array size
    static constexpr SizeType ConditionsArraySize = (Dimension == 2) ? 1 : 2;

    /// Elements array size
    static constexpr SizeType ElementsArraySize = (Dimension == 2) ? 1 : 2;

    /// The type of array considered for the tensor
    typedef typename std::conditional<Dimension == 2, array_1d<double, 3>, array_1d<double, 6>>::type TensorArrayType;

    /// Double vector
    typedef std::vector<double> DoubleVectorType;

    /// Double vector map
    typedef std::unordered_map<DoubleVectorType, IndexType, KeyHasherRange<DoubleVectorType>, KeyComparorRange<DoubleVectorType> > DoubleVectorMapType;

    /// Index vector map
    typedef std::unordered_map<IndexVectorType, IndexType, KeyHasherRange<IndexVectorType>, KeyComparorRange<IndexVectorType> > IndexVectorMapType;

    ///@}
    ///@name  Enum's
    ///@{

    ///@}
    ///@name Life Cycle
    ///@{

    ///@}
    ///@name Access
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Input and output
    ///@{

    ///@}
    ///@name Friends
    ///@{

    ///@}
    ///@name Operators
    ///@{

    ///@}
    ///@name Operations
    ///@{

    /**
     * @brief It prints info about the current mesh
     * @param rNumberOfNodes The number of nodes
     * @param rNumberOfConditions The number of conditions
     * @param rNumberOfElements The number of elements
     * @param EchoLevel The level of verbosity
     */
    void PrintMmgMeshInfo(
        SizeType& rNumberOfNodes,
        array_1d<SizeType, 2>& rNumberOfConditions,
        array_1d<SizeType, 2>& rNumberOfElements,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief It checks if the nodes are repeated and remove the repeated ones
     * @param rModelPart The model part of interest to study
     * @param EchoLevel The level of verbosity
     */
    IndexVectorType CheckNodes(
        ModelPart& rModelPart,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief It checks if the conditions are repeated and remove the repeated ones
     * @param EchoLevel The level of verbosity
     */
    IndexVectorType CheckConditions0(const IndexType EchoLevel = 0);

    /**
     * @brief It checks if the conditions are repeated and remove the repeated ones
     * @param EchoLevel The level of verbosity
     */
    IndexVectorType CheckConditions1(const IndexType EchoLevel = 0);

    /**
     * @brief It checks if the elemenst are removed and remove the repeated ones
     * @param EchoLevel The level of verbosity
     */
    IndexVectorType CheckElements0(const IndexType EchoLevel = 0);

    /**
     * @brief It checks if the elemenst are removed and remove the repeated ones
     * @param EchoLevel The level of verbosity
     */
    IndexVectorType CheckElements1(const IndexType EchoLevel = 0);

    /**
     * @brief It blocks certain nodes before remesh the model
     * @param iNode The index of the node
     */
    void BlockNode(const IndexType iNode);

    /**
     * @brief It blocks certain conditions before remesh the model
     * @param iCondition The index of the condition
     */
    void BlockCondition(const IndexType iCondition);

    /**
     * @brief It blocks certain elements before remesh the model
     * @param iElement The index of the element
     */
    void BlockElement(const IndexType iElement);

    /**
     * @brief It creates the new node
     * @param rModelPart The model part of interest to study
     * @param iNode The index of the new noode
     * @param Ref The submodelpart id
     * @param IsRequired MMG value (I don't know that it does)
     * @param EchoLevel The level of verbosity
     * @return pNode The pointer to the new node created
     */
    NodeType::Pointer CreateNode(
        ModelPart& rModelPart,
        IndexType iNode,
        int& Ref,
        int& IsRequired,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief It creates the new condition
     * @param rModelPart The model part of interest to study
     * @param rMapPointersRefCondition The pointer to the condition of reference
     * @param CondId The id of the condition
     * @param PropId The submodelpart id
     * @param IsRequired MMG value (I don't know that it does)
     * @param RemoveRegions Cuttig-out specified regions during surface remeshing
     * @param Discretization The discretization option
     * @param EchoLevel The level of verbosity
     * @return pCondition The pointer to the new condition created
     */
    Condition::Pointer CreateCondition0(
        ModelPart& rModelPart,
        std::unordered_map<IndexType,Condition::Pointer>& rMapPointersRefCondition,
        const IndexType CondId,
        int& PropId,
        int& IsRequired,
        bool SkipCreation,
        const bool RemoveRegions = false,
        const DiscretizationOption Discretization = DiscretizationOption::STANDARD,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief It creates the new condition
     * @param rModelPart The model part of interest to study
     * @param rMapPointersRefCondition The pointer to the condition of reference
     * @param CondId The id of the condition
     * @param PropId The submodelpart id
     * @param IsRequired MMG value (I don't know that it does)
     * @param RemoveRegions Cuttig-out specified regions during surface remeshing
     * @param Discretization The discretization option
     * @param EchoLevel The level of verbosity
     * @return pCondition The pointer to the new condition created
     */
    Condition::Pointer CreateCondition1(
        ModelPart& rModelPart,
        std::unordered_map<IndexType,Condition::Pointer>& rMapPointersRefCondition,
        const IndexType CondId,
        int& PropId,
        int& IsRequired,
        bool SkipCreation,
        const bool RemoveRegions = false,
        const DiscretizationOption Discretization = DiscretizationOption::STANDARD,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief It creates the new element
     * @param rModelPart The model part of interest to study
     * @param rMapPointersRefElement The pointer to the element of reference
     * @param ElemId The id of the element
     * @param PropId The submodelpart id
     * @param IsRequired MMG value (I don't know that it does)
     * @param RemoveRegions Cuttig-out specified regions during surface remeshing
     * @param Discretization The discretization option
     * @param EchoLevel The level of verbosity
     * @return pElement The pointer to the new condition created
     */
    Element::Pointer CreateElement0(
        ModelPart& rModelPart,
        std::unordered_map<IndexType,Element::Pointer>& rMapPointersRefElement,
        const IndexType ElemId,
        int& PropId,
        int& IsRequired,
        bool SkipCreation,
        const bool RemoveRegions = false,
        const DiscretizationOption Discretization = DiscretizationOption::STANDARD,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief It creates the new element
     * @param rModelPart The model part of interest to study
     * @param rMapPointersRefElement The pointer to the element of reference
     * @param ElemId The id of the element
     * @param PropId The submodelpart id
     * @param IsRequired MMG value (I don't know that it does)
     * @param RemoveRegions Cuttig-out specified regions during surface remeshing
     * @param Discretization The discretization option
     * @param EchoLevel The level of verbosity
     * @return pElement The pointer to the new condition created
     */
    Element::Pointer CreateElement1(
        ModelPart& rModelPart,
        std::unordered_map<IndexType,Element::Pointer>& rMapPointersRefElement,
        const IndexType ElemId,
        int& PropId,
        int& IsRequired,
        bool SkipCreation,
        const bool RemoveRegions = false,
        const DiscretizationOption Discretization = DiscretizationOption::STANDARD,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief Initialisation of mesh and sol structures
     * @details Initialisation of mesh and sol structures args of InitMesh:
     * -# MMG5_ARG_start we start to give the args of a variadic func
     * -# MMG5_ARG_ppMesh next arg will be a pointer over a MMG5_pMesh
     * -# &mmgMesh pointer toward your MMG5_pMesh (that store your mesh)
     * -# MMG5_ARG_ppMet next arg will be a pointer over a MMG5_pSol storing a metric
     * -# &mmgSol pointer toward your MMG5_pSol (that store your metric)
     * @param Discretization The discretization type
     */
    void InitMesh(
        DiscretizationOption Discretization = DiscretizationOption::STANDARD,
        const IndexType EchoLevel = 0
        );

    /**
     * @brief Here the verbosity is set
     */
    void InitVerbosity(IndexType EchoLevel);

    /**
     * @brief Here the verbosity is set using the API
     * @param VerbosityMMG The equivalent verbosity level in the MMG API
     */
    void InitVerbosityParameter(const IndexType VerbosityMMG);

    /**
     * @brief This sets the size of the mesh
     * @param NumArrayElements Number of Elements
     * @param NumArrayConditions Number of Conditions
     */
    void SetMeshSize(
        const SizeType NumNodes,
        const array_1d<SizeType, ElementsArraySize>& NumArrayElements,
        const array_1d<SizeType, ConditionsArraySize>& NumArrayConditions
        );

    /**
     * @brief This sets the size of the solution for the scalar case
     * @param NumNodes Number of nodes
     */
    void SetSolSizeScalar(const SizeType NumNodes);

    /**
     * @brief This sets the size of the solution for the vector case
     * @param NumNodes Number of nodes
     */
    void SetSolSizeVector(const SizeType NumNodes);

    /**
     * @brief This sets the size of the solution for the tensor case
     * @param NumNodes Number of nodes
     */
    void SetSolSizeTensor(const SizeType NumNodes);

    /**
     * @brief This checks the mesh data and prints if it is OK
     */
    void CheckMeshData();

    /**
     * @brief This sets the output mesh
     * @param rInputName The input name
     * @param PostOutput If the ouput file is the solution after take into account the metric or not
     * @param Step The step to postprocess
     */
    void InputMesh(const std::string& rInputName);

    /**
     * @brief This sets the output sol
     * @param rInputName The input name
     */
    void InputSol(const std::string& rInputName);

    /**
     * @brief This sets the output mesh
     * @param rOutputName The output name
     * @param PostOutput If the ouput file is the solution after take into account the metric or not
     * @param Step The step to postprocess
     */
    void OutputMesh(
        const std::string& rOutputName,
        const bool PostOutput,
        const IndexType Step
        );

    /**
     * @brief This sets the output sol
     * @param rOutputName The output name
     * @param PostOutput If the ouput file is the solution after take into account the metric or not
     * @param Step The step to postprocess
     */
    void OutputSol(
        const std::string& rOutputName,
        const bool PostOutput,
        const IndexType Step
        );

    /**
     * @brief This frees the MMG structures
     */
    void FreeAll();

    /**
     * @brief This loads the solution
     */
    void MMGLibCallMetric(Parameters ConfigurationParameters);

    /**
     * @brief This loads the solution
     */
    void MMGLibCallIsoSurface(Parameters ConfigurationParameters);

    /**
     * @brief This sets the nodes of the mesh
     * @param X Coordinate X
     * @param Y Coordinate Y
     * @param Z Coordinate Z
     * @param Color Reference of the node(submodelpart)
     * @param Index The index number of the node
     */
    void SetNodes(
        const double X,
        const double Y,
        const double Z,
        const IndexType Color,
        const IndexType Index
        );

    /**
     * @brief This sets the conditions of the mesh
     * @param rGeometry The geometry of the condition
     * @param Color Reference of the node(submodelpart)
     * @param Index The index number of the node
     */
    void SetConditions(
        GeometryType& rGeometry,
        const IndexType Color,
        const IndexType Index
        );

    /**
     * @brief This sets elements of the mesh
     * @param rGeometry The geometry of the element
     * @param Color Reference of the node(submodelpart)
     * @param Index The index number of the node
     */
    void SetElements(
        GeometryType& rGeometry,
        const IndexType Color,
        const IndexType Index
        );

    /**
     * @brief This function is used to compute the metric scalar
     * @param Metric The inverse of the size node
     * @param NodeId The id of the node
     */
    void SetMetricScalar(
        const double Metric,
        const IndexType NodeId
        );

    /**
     * @brief This function is used to compute the metric vector (x, y, z)
     * @param Metric This array contains the components of the metric vector
     * @param NodeId The id of the node
     */
    void SetMetricVector(
        const array_1d<double, Dimension>& Metric,
        const IndexType NodeId
        );

    /**
     * @brief This function is used to compute the Hessian metric tensor, note that when using the Hessian, more than one metric can be defined simultaneously, so in consecuence we need to define the elipsoid which defines the volume of maximal intersection
     * @param Metric This array contains the components of the metric tensor in the MMG defined order
     * @param NodeId The id of the node
     */
    void SetMetricTensor(
        const TensorArrayType& Metric,
        const IndexType NodeId
        );

    ///@}
    ///@name Access
    ///@{


    ///@}
    ///@name Inquiry
    ///@{


    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    std::string Info() const // override
    {
        return "MmgUtilities";
    }

    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const // override
    {
        rOStream << "MmgUtilities";
    }

    /// Print object's data.
    void PrintData(std::ostream& rOStream) const // override
    {
    }

protected:

    ///@name Protected Member Variables
    ///@{

    ///@}
    ///@name Protected member Variables
    ///@{

    ///@}
    ///@name Protected Operators
    ///@{

    ///@}
    ///@name Protected Operations
    ///@{

    ///@}
    ///@name Protected  Access
    ///@{

    ///@}
    ///@name Protected Inquiry
    ///@{

    ///@}
    ///@name Protected LifeCycle
    ///@{

    ///@}

private:
    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    ///@}
    ///@name Private Operators
    ///@{

    ///@}
    ///@name Private Operations
    ///@{

    ///@}
    ///@name Private  Access
    ///@{


    ///@}
    ///@name Private Inquiry
    ///@{


    ///@}
    ///@name Un accessible methods
    ///@{

//     /// Assignment operator.
//     MmgUtilities& operator=(MmgUtilities const& rOther);

//     /// Copy constructor.
//     MmgUtilities(MmgUtilities const& rOther);

    ///@}

};// class MmgUtilities
///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{

/// input stream function
template<MMGLibrary TMMGLibray>
inline std::istream& operator >> (std::istream& rIStream,
                                  MmgUtilities<TMMGLibray>& rThis);

/// output stream function
template<MMGLibrary TMMGLibray>
inline std::ostream& operator << (std::ostream& rOStream,
                                  const MmgUtilities<TMMGLibray>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}

}// namespace Kratos.
#endif /* KRATOS_MMG_UTILITIES defined */
