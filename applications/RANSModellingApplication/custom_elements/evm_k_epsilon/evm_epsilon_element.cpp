//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya (https://github.com/sunethwarna)
//

// System includes

// External includes

// Include Base h
#include "evm_epsilon_element.h"

namespace Kratos
{
///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

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
 * Constructor.
 */
template <unsigned int TDim, unsigned int TNumNodes>
EvmEpsilonElement<TDim, TNumNodes>::EvmEpsilonElement(IndexType NewId)
    : StabilizedConvectionDiffusionReactionElement<TDim, TNumNodes, EvmEpsilonElementData>(NewId)
{
}

/**
 * Constructor using an array of nodes
 */
template <unsigned int TDim, unsigned int TNumNodes>
EvmEpsilonElement<TDim, TNumNodes>::EvmEpsilonElement(IndexType NewId,
                                                      const NodesArrayType& ThisNodes)
    : StabilizedConvectionDiffusionReactionElement<TDim, TNumNodes, EvmEpsilonElementData>(
          NewId, ThisNodes)
{
}

/**
 * Constructor using Geometry
 */
template <unsigned int TDim, unsigned int TNumNodes>
EvmEpsilonElement<TDim, TNumNodes>::EvmEpsilonElement(IndexType NewId, GeometryType::Pointer pGeometry)
    : StabilizedConvectionDiffusionReactionElement<TDim, TNumNodes, EvmEpsilonElementData>(
          NewId, pGeometry)
{
}

/**
 * Constructor using Properties
 */
template <unsigned int TDim, unsigned int TNumNodes>
EvmEpsilonElement<TDim, TNumNodes>::EvmEpsilonElement(IndexType NewId,
                                                      GeometryType::Pointer pGeometry,
                                                      PropertiesType::Pointer pProperties)
    : StabilizedConvectionDiffusionReactionElement<TDim, TNumNodes, EvmEpsilonElementData>(
          NewId, pGeometry, pProperties)
{
}

/**
 * Copy Constructor
 */
template <unsigned int TDim, unsigned int TNumNodes>
EvmEpsilonElement<TDim, TNumNodes>::EvmEpsilonElement(EvmEpsilonElement<TDim, TNumNodes> const& rOther)
    : StabilizedConvectionDiffusionReactionElement<TDim, TNumNodes, EvmEpsilonElementData>(rOther)
{
}

/**
 * Destructor
 */
template <unsigned int TDim, unsigned int TNumNodes>
EvmEpsilonElement<TDim, TNumNodes>::~EvmEpsilonElement()
{
}

///@}
///@name Operators
///@{

/// Assignment operator.
template <unsigned int TDim, unsigned int TNumNodes>
EvmEpsilonElement<TDim, TNumNodes>& EvmEpsilonElement<TDim, TNumNodes>::operator=(
    EvmEpsilonElement<TDim, TNumNodes> const& rOther)
{
    BaseType::operator=(rOther);
    Flags::operator=(rOther);
    // mpProperties = rOther.mpProperties;
    return *this;
}

///@}
///@name Operations
///@{

/**
 * ELEMENTS inherited from this class have to implement next
 * Create and Clone methods: MANDATORY
 */

/**
 * creates a new element pointer
 * @param NewId: the ID of the new element
 * @param ThisNodes: the nodes of the new element
 * @param pProperties: the properties assigned to the new element
 * @return a Pointer to the new element
 */
template <unsigned int TDim, unsigned int TNumNodes>
Element::Pointer EvmEpsilonElement<TDim, TNumNodes>::Create(IndexType NewId,
                                                            NodesArrayType const& ThisNodes,
                                                            PropertiesType::Pointer pProperties) const
{
    KRATOS_TRY
    return Kratos::make_intrusive<EvmEpsilonElement>(
        NewId, Element::GetGeometry().Create(ThisNodes), pProperties);
    KRATOS_CATCH("");
}

/**
 * creates a new element pointer
 * @param NewId: the ID of the new element
 * @param pGeom: the geometry to be employed
 * @param pProperties: the properties assigned to the new element
 * @return a Pointer to the new element
 */
template <unsigned int TDim, unsigned int TNumNodes>
Element::Pointer EvmEpsilonElement<TDim, TNumNodes>::Create(IndexType NewId,
                                                            GeometryType::Pointer pGeom,
                                                            PropertiesType::Pointer pProperties) const
{
    KRATOS_TRY
    return Kratos::make_intrusive<EvmEpsilonElement>(NewId, pGeom, pProperties);
    KRATOS_CATCH("");
}

/**
 * creates a new element pointer and clones the previous element data
 * @param NewId: the ID of the new element
 * @param ThisNodes: the nodes of the new element
 * @param pProperties: the properties assigned to the new element
 * @return a Pointer to the new element
 */
template <unsigned int TDim, unsigned int TNumNodes>
Element::Pointer EvmEpsilonElement<TDim, TNumNodes>::Clone(IndexType NewId,
                                                           NodesArrayType const& ThisNodes) const
{
    KRATOS_TRY
    return Kratos::make_intrusive<EvmEpsilonElement>(
        NewId, Element::GetGeometry().Create(ThisNodes), Element::pGetProperties());
    KRATOS_CATCH("");
}

/**
 * this determines the elemental equation ID vector for all elemental
 * DOFs
 * @param rResult: the elemental equation ID vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::EquationIdVector(EquationIdVectorType& rResult,
                                                          ProcessInfo& CurrentProcessInfo)
{
    if (rResult.size() != TNumNodes)
        rResult.resize(TNumNodes, false);

    for (unsigned int i = 0; i < TNumNodes; i++)
        rResult[i] =
            Element::GetGeometry()[i].GetDof(TURBULENT_ENERGY_DISSIPATION_RATE).EquationId();
}

/**
 * determines the elemental list of DOFs
 * @param ElementalDofList: the list of DOFs
 * @param rCurrentProcessInfo: the current process info instance
 */
template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::GetDofList(DofsVectorType& rElementalDofList,
                                                    ProcessInfo& rCurrentProcessInfo)
{
    if (rElementalDofList.size() != TNumNodes)
        rElementalDofList.resize(TNumNodes);

    for (unsigned int i = 0; i < TNumNodes; i++)
        rElementalDofList[i] =
            Element::GetGeometry()[i].pGetDof(TURBULENT_ENERGY_DISSIPATION_RATE);
}

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::GetValuesVector(VectorType& rValues, int Step)
{
    this->GetFirstDerivativesVector(rValues, Step);
}

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::GetFirstDerivativesVector(VectorType& rValues, int Step)
{
    if (rValues.size() != TNumNodes)
        rValues.resize(TNumNodes, false);

    GeometryType& rGeom = this->GetGeometry();
    IndexType LocalIndex = 0;
    for (IndexType iNode = 0; iNode < TNumNodes; ++iNode)
    {
        rValues[LocalIndex++] = rGeom[iNode].FastGetSolutionStepValue(
            TURBULENT_ENERGY_DISSIPATION_RATE, Step);
    }
}

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::GetSecondDerivativesVector(VectorType& rValues, int Step)
{
    if (rValues.size() != TNumNodes)
        rValues.resize(TNumNodes, false);

    GeometryType& rGeom = this->GetGeometry();
    IndexType LocalIndex = 0;
    for (IndexType iNode = 0; iNode < TNumNodes; ++iNode)
    {
        rValues[LocalIndex++] = rGeom[iNode].FastGetSolutionStepValue(
            TURBULENT_ENERGY_DISSIPATION_RATE_2, Step);
    }
}
template <unsigned int TDim, unsigned int TNumNodes>
GeometryData::IntegrationMethod EvmEpsilonElement<TDim, TNumNodes>::GetIntegrationMethod() const
{
    return GeometryData::GI_GAUSS_2;
}

/**
 * This method provides the place to perform checks on the completeness of the
 * input and the compatibility with the problem options as well as the
 * contitutive laws selected It is designed to be called only once (or anyway,
 * not often) typically at the beginning of the calculations, so to verify that
 * nothing is missing from the input or that no common error is found.
 * @param rCurrentProcessInfo
 * this method is: MANDATORY
 */
template <unsigned int TDim, unsigned int TNumNodes>
int EvmEpsilonElement<TDim, TNumNodes>::Check(const ProcessInfo& rCurrentProcessInfo)
{
    KRATOS_TRY

    BaseType::Check(rCurrentProcessInfo);

    KRATOS_CHECK_VARIABLE_KEY(TURBULENCE_RANS_C1);
    KRATOS_CHECK_VARIABLE_KEY(TURBULENCE_RANS_C2);
    KRATOS_CHECK_VARIABLE_KEY(TURBULENCE_RANS_C_MU);
    KRATOS_CHECK_VARIABLE_KEY(TURBULENT_ENERGY_DISSIPATION_RATE_SIGMA);
    KRATOS_CHECK_VARIABLE_KEY(KINEMATIC_VISCOSITY);
    KRATOS_CHECK_VARIABLE_KEY(TURBULENT_VISCOSITY);
    KRATOS_CHECK_VARIABLE_KEY(TURBULENT_KINETIC_ENERGY);
    KRATOS_CHECK_VARIABLE_KEY(TURBULENT_ENERGY_DISSIPATION_RATE);
    KRATOS_CHECK_VARIABLE_KEY(TURBULENT_ENERGY_DISSIPATION_RATE_2);
    // KRATOS_CHECK_VARIABLE_KEY(RANS_Y_PLUS);
    // KRATOS_CHECK_VARIABLE_KEY(DISTANCE);
    KRATOS_CHECK_VARIABLE_KEY(RANS_AUXILIARY_VARIABLE_2);

    for (IndexType iNode = 0; iNode < this->GetGeometry().size(); ++iNode)
    {
        NodeType& r_node = this->GetGeometry()[iNode];

        KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(KINEMATIC_VISCOSITY, r_node);
        KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(TURBULENT_VISCOSITY, r_node);
        KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(TURBULENT_KINETIC_ENERGY, r_node);
        KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(TURBULENT_ENERGY_DISSIPATION_RATE, r_node);
        KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(TURBULENT_ENERGY_DISSIPATION_RATE_2, r_node);
        // KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(RANS_Y_PLUS, r_node);
        KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(RANS_AUXILIARY_VARIABLE_2, r_node);
        // KRATOS_CHECK_VARIABLE_IN_NODAL_DATA(DISTANCE, r_node);

        KRATOS_CHECK_DOF_IN_NODE(TURBULENT_ENERGY_DISSIPATION_RATE, r_node);
    }

    return 0;

    KRATOS_CATCH("");
}

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

template <unsigned int TDim, unsigned int TNumNodes>
std::string EvmEpsilonElement<TDim, TNumNodes>::Info() const
{
    std::stringstream buffer;
    buffer << "EvmEpsilonElement #" << Element::Id();
    return buffer.str();
}

/// Print information about this object.

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::PrintInfo(std::ostream& rOStream) const
{
    rOStream << "EvmEpsilonElement #" << Element::Id();
}

/// Print object's data.

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::PrintData(std::ostream& rOStream) const
{
    Element::pGetGeometry()->PrintData(rOStream);
}

///@}
///@name Friends
///@{

///@}

///@name Protected static Member Variables
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

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::CalculateConvectionDiffusionReactionData(
    EvmEpsilonElementData& rData,
    double& rEffectiveKinematicViscosity,
    const Vector& rShapeFunctions,
    const Matrix& rShapeFunctionDerivatives,
    const ProcessInfo& rCurrentProcessInfo,
    const int Step) const
{
    const double c1 = rCurrentProcessInfo[TURBULENCE_RANS_C1];
    const double c2 = rCurrentProcessInfo[TURBULENCE_RANS_C2];
    const double c_mu = rCurrentProcessInfo[TURBULENCE_RANS_C_MU];
    const double epsilon_sigma =
        rCurrentProcessInfo[TURBULENT_ENERGY_DISSIPATION_RATE_SIGMA];

    const double nu = this->EvaluateInPoint(KINEMATIC_VISCOSITY, rShapeFunctions);
    const double nu_t = this->EvaluateInPoint(TURBULENT_VISCOSITY, rShapeFunctions);
    const double tke = this->EvaluateInPoint(TURBULENT_KINETIC_ENERGY, rShapeFunctions);
    // const double epsilon =
    //     this->EvaluateInPoint(TURBULENT_ENERGY_DISSIPATION_RATE, rShapeFunctions);
    const double gamma = EvmKepsilonModelUtilities::CalculateGamma(c_mu, 1.0, tke, nu_t);
    // const double gamma = tke / (epsilon + std::numeric_limits<double>::epsilon());
    // const double wall_distance = this->EvaluateInPoint(DISTANCE, rShapeFunctions);
    // const double y_plus = this->EvaluateInPoint(RANS_Y_PLUS, rShapeFunctions);

    rData.C1 = c1;
    rData.C2 = c2;
    rData.Gamma = gamma;
    rData.ShapeFunctionDerivatives = rShapeFunctionDerivatives;
    rData.TurbulentKinematicViscosity = nu_t;
    rData.TurbulentKineticEnergy = tke;
    // rData.WallDistance = wall_distance;
    // rData.WallNormal = this->EvaluateInPoint(NORMAL, rShapeFunctions);
    rData.VelocityDivergence =
        this->GetDivergenceOperator(VELOCITY, rShapeFunctionDerivatives);
    // rData.YPlus = y_plus;
    // rData.WallVelocity = norm_2(this->EvaluateInPoint(VELOCITY, rShapeFunctions));

    rEffectiveKinematicViscosity = nu + nu_t / epsilon_sigma;
}

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::CalculateConvectionDiffusionReactionData(
    EvmEpsilonElementData& rData,
    double& rEffectiveKinematicViscosity,
    double& rVariableGradientNorm,
    double& rVariableRelaxedAcceleration,
    const Vector& rShapeFunctions,
    const Matrix& rShapeFunctionDerivatives,
    const ProcessInfo& rCurrentProcessInfo,
    const int Step) const
{
    this->CalculateConvectionDiffusionReactionData(
        rData, rEffectiveKinematicViscosity, rShapeFunctions,
        rShapeFunctionDerivatives, rCurrentProcessInfo, Step);

    array_1d<double, 3> epsilon_gradient;
    this->CalculateGradient(epsilon_gradient, TURBULENT_ENERGY_DISSIPATION_RATE,
                            rShapeFunctionDerivatives);
    rVariableGradientNorm = norm_2(epsilon_gradient);

    rVariableRelaxedAcceleration =
        this->EvaluateInPoint(RANS_AUXILIARY_VARIABLE_2, rShapeFunctions);
}

template <unsigned int TDim, unsigned int TNumNodes>
double EvmEpsilonElement<TDim, TNumNodes>::CalculateReactionTerm(
    const EvmEpsilonElementData& rData, const ProcessInfo& rCurrentProcessInfo, const int Step) const
{
    return rData.C2 * rData.Gamma + rData.C1 * 2.0 * rData.VelocityDivergence / 3.0;
}

template <unsigned int TDim, unsigned int TNumNodes>
double EvmEpsilonElement<TDim, TNumNodes>::CalculateSourceTerm(const EvmEpsilonElementData& rData,
                                                               const ProcessInfo& rCurrentProcessInfo,
                                                               const int Step) const
{
    double production = 0.0;
    // const double c_mu = rCurrentProcessInfo[TURBULENCE_RANS_C_MU];
    // const double von_karman = rCurrentProcessInfo[WALL_VON_KARMAN];
    // const double beta = rCurrentProcessInfo[WALL_SMOOTHNESS_BETA];
    BoundedMatrix<double, TDim, TDim> velocity_gradient_matrix;
    this->CalculateGradient(velocity_gradient_matrix, VELOCITY, rData.ShapeFunctionDerivatives);

    // if (this->Is(STRUCTURE))
    // {
    //     // Calculate the wall production term
    //     const double u_tau = std::max(
    //         std::pow(c_mu, 0.25) * std::sqrt(std::max(rData.TurbulentKineticEnergy, 0.0)),
    //         rData.WallVelocity / (std::log(rData.YPlus) / von_karman + beta));
    //     production = std::pow(u_tau, 3) / (von_karman * rData.WallDistance);
    // }
    // else
    // {
        production = EvmKepsilonModelUtilities::CalculateSourceTerm<TDim>(
            velocity_gradient_matrix, rData.TurbulentKinematicViscosity,
            rData.TurbulentKineticEnergy);
    // }

    production *= (rData.C1 * rData.Gamma);
    return production;
}

template <>
void EvmEpsilonElement<2, 3>::Initialize()
{
    const GeometryType& r_geometry = this->GetGeometry();
    const GeometryType::GeometriesArrayType& r_condition_point_list =
        r_geometry.GenerateEdges();

    if (EvmKepsilonModelUtilities::HasConditionWithFlag<NodeType>(
            r_condition_point_list, STRUCTURE))
        this->Set(STRUCTURE, true);
}

template <>
void EvmEpsilonElement<2, 4>::Initialize()
{
    const GeometryType& r_geometry = this->GetGeometry();
    const GeometryType::GeometriesArrayType& r_condition_point_list =
        r_geometry.GenerateEdges();

    if (EvmKepsilonModelUtilities::HasConditionWithFlag<NodeType>(
            r_condition_point_list, STRUCTURE))
        this->Set(STRUCTURE, true);
}

template <>
void EvmEpsilonElement<3, 4>::Initialize()
{
    const GeometryType& r_geometry = this->GetGeometry();
    const GeometryType::GeometriesArrayType& r_condition_point_list =
        r_geometry.GenerateFaces();

    if (EvmKepsilonModelUtilities::HasConditionWithFlag<NodeType>(
            r_condition_point_list, STRUCTURE))
        this->Set(STRUCTURE, true);
}

template <>
void EvmEpsilonElement<3, 8>::Initialize()
{
    const GeometryType& r_geometry = this->GetGeometry();
    const GeometryType::GeometriesArrayType& r_condition_point_list =
        r_geometry.GenerateFaces();

    if (EvmKepsilonModelUtilities::HasConditionWithFlag<NodeType>(
            r_condition_point_list, STRUCTURE))
        this->Set(STRUCTURE, true);
}
///@}
///@name Serialization
///@{

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::save(Serializer& rSerializer) const
{
    KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, Element);

    // List
    // To be completed with the class member list
}

template <unsigned int TDim, unsigned int TNumNodes>
void EvmEpsilonElement<TDim, TNumNodes>::load(Serializer& rSerializer)
{
    KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, Element);

    // List
    // To be completed with the class member list
}

///@}
///@name Private  Access
///@{

///@}
///@name Private Inquiry
///@{

///@}
///@name Un accessible methods
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

/// input stream function

template <unsigned int TDim, unsigned int TNumNodes>
inline std::istream& operator>>(std::istream& rIStream,
                                EvmEpsilonElement<TDim, TNumNodes>& rThis);

/// output stream function

template <unsigned int TDim, unsigned int TNumNodes>
inline std::ostream& operator<<(std::ostream& rOStream,
                                const EvmEpsilonElement<TDim, TNumNodes>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << " : " << std::endl;
    rThis.PrintData(rOStream);
    return rOStream;
}

// Class template instantiation

template class EvmEpsilonElement<2, 3>;
template class EvmEpsilonElement<3, 4>;
template class EvmEpsilonElement<2, 4>;
template class EvmEpsilonElement<3, 8>;

} // namespace Kratos.
