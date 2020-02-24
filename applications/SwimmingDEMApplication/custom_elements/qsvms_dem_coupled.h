//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Jordi Cotela
//

#ifndef KRATOS_QSVMS_DEM_COUPLED_H
#define KRATOS_QSVMS_DEM_COUPLED_H

// System includes
#include <string>
#include <iostream>

#include "includes/checks.h"
#include "containers/array_1d.h"
#include "includes/define.h"
#include "includes/element.h"
#include "includes/serializer.h"
#include "geometries/geometry.h"
#include "utilities/geometry_utilities.h"

#include "includes/cfd_variables.h"
#include "../../applications/FluidDynamicsApplication/custom_elements/qs_vms.h"
#include "../../applications/FluidDynamicsApplication/fluid_dynamics_application_variables.h"

namespace Kratos
{

///@addtogroup FluidDynamicsApplication
///@{

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

template< class TElementData >
class KRATOS_API(SWIMMING_DEM_APPLICATION) QSVMSDEMCoupled : public QSVMS<TElementData>
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of QSVMSDEMCoupled
    KRATOS_CLASS_INTRUSIVE_POINTER_DEFINITION(QSVMSDEMCoupled);

    /// Node type (default is: Node<3>)
    typedef Node<3> NodeType;

    /// Geometry type (using with given NodeType)
    typedef Geometry<NodeType> GeometryType;

    /// Definition of nodes container type, redefined from GeometryType
    typedef Geometry<NodeType>::PointsArrayType NodesArrayType;

    /// Vector type for local contributions to the linear system
    typedef Vector VectorType;

    /// Matrix type for local contributions to the linear system
    typedef Matrix MatrixType;

    typedef std::size_t IndexType;

    typedef std::size_t SizeType;

    typedef std::vector<std::size_t> EquationIdVectorType;

    typedef std::vector< Dof<double>::Pointer > DofsVectorType;

    typedef PointerVectorSet<Dof<double>, IndexedObject> DofsArrayType;

    /// Type for shape function values container
    typedef Kratos::Vector ShapeFunctionsType;

    /// Type for a matrix containing the shape function gradients
    typedef Kratos::Matrix ShapeFunctionDerivativesType;

    /// Type for an array of shape function gradient matrices
    typedef GeometryType::ShapeFunctionsGradientsType ShapeFunctionDerivativesArrayType;

    constexpr static unsigned int Dim = QSVMS<TElementData>::Dim;
    constexpr static unsigned int NumNodes = QSVMS<TElementData>::NumNodes;
    constexpr static unsigned int BlockSize = QSVMS<TElementData>::BlockSize;
    constexpr static unsigned int LocalSize = QSVMS<TElementData>::LocalSize;
    constexpr static unsigned int StrainSize = QSVMS<TElementData>::StrainSize;

    ///@}
    ///@name Life Cycle
    ///@{

    //Constructors.

    /// Default constuctor.
    /**
     * @param NewId Index number of the new element (optional)
     */
    QSVMSDEMCoupled(IndexType NewId = 0);

    /// Constructor using an array of nodes.
    /**
     * @param NewId Index of the new element
     * @param ThisNodes An array containing the nodes of the new element
     */
    QSVMSDEMCoupled(IndexType NewId, const NodesArrayType& ThisNodes);

    /// Constructor using a geometry object.
    /**
     * @param NewId Index of the new element
     * @param pGeometry Pointer to a geometry object
     */
    QSVMSDEMCoupled(IndexType NewId, GeometryType::Pointer pGeometry);

    /// Constuctor using geometry and properties.
    /**
     * @param NewId Index of the new element
     * @param pGeometry Pointer to a geometry object
     * @param pProperties Pointer to the element's properties
     */
    QSVMSDEMCoupled(IndexType NewId, GeometryType::Pointer pGeometry, Properties::Pointer pProperties);

    /// Destructor.
    virtual ~QSVMSDEMCoupled() override;

    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{


    /// Create a new element of this type
    /**
     * Returns a pointer to a new QSVMSDEMCoupled element, created using given input
     * @param NewId the ID of the new element
     * @param ThisNodes the nodes of the new element
     * @param pProperties the properties assigned to the new element
     * @return a Pointer to the new element
     */
    Element::Pointer Create(IndexType NewId,
                            NodesArrayType const& ThisNodes,
                            Properties::Pointer pProperties) const override;

    /// Create a new element of this type using given geometry
    /**
     * Returns a pointer to a new FluidElement element, created using given input
     * @param NewId the ID of the new element
     * @param pGeom a pointer to the geomerty to be used to create the element
     * @param pProperties the properties assigned to the new element
     * @return a Pointer to the new element
     */
     Element::Pointer Create(IndexType NewId,
                             GeometryType::Pointer pGeom,
                             Properties::Pointer pProperties) const override;


    /**
     * clones the selected element variables, creating a new one
     * @param NewId: the ID of the new element
     * @param ThisNodes: the nodes of the new element
     * @param pProperties: the properties assigned to the new element
     * @return a Pointer to the new element
     */

    ///@}
    ///@name Access
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    void Calculate(
        const Variable<double>& rVariable,
        double& rOutput,
        const ProcessInfo& rCurrentProcessInfo) override;

    void Calculate(const Variable<array_1d<double, 3>>& rVariable,
                   array_1d<double, 3>& rOutput,
                   const ProcessInfo& rCurrentProcessInfo) override;

    void Calculate(
        const Variable<Vector >& rVariable,
        Vector& Output,
        const ProcessInfo& rCurrentProcessInfo) override;

    void Calculate(
        const Variable<Matrix >& rVariable,
        Matrix& Output,
        const ProcessInfo& rCurrentProcessInfo) override;


    void EquationIdVector(EquationIdVectorType& rResult,
                          ProcessInfo& rCurrentProcessInfo) override;

    void GetDofList(DofsVectorType& rElementalDofList,
                    ProcessInfo& rCurrentProcessInfo) override;

    double FilterWidth();

    double FilterWidth(const BoundedMatrix<double, NumNodes, Dim >& DN_DX);

    void CalculateLocalSystem(MatrixType& rLeftHandSideMatrix,
                              VectorType& rRightHandSideVector,
                              ProcessInfo& rCurrentProcessInfo) override;

    void CalculateLeftHandSide(MatrixType& rLeftHandSideMatrix,
                               ProcessInfo& rCurrentProcessInfo) override;

    void CalculateRightHandSide(VectorType& rRightHandSideVector,
                                ProcessInfo& rCurrentProcessInfo) override;

    void AddMassStabilization(TElementData& rData,
                              MatrixType &rMassMatrix) override;

    void CalculateLaplacianMassMatrix(MatrixType& rMassMatrix, ProcessInfo& rCurrentProcessInfo);

    void GetAdvectiveVelDivergence(double & rAdvVelDiv, const BoundedMatrix<double, NumNodes, Dim >& rDN_DX);

    void CalculateLaplacianLumpedMassMatrix(MatrixType& rLHSMatrix, const double Mass);

    void AddRHSLaplacian(VectorType& F,
                        const BoundedMatrix<double, NumNodes, Dim>& rDN_DX,
                        const double Weight);

    void AlgebraicMomentumResidual(const TElementData& rData, const array_1d<double,3> &rConvectionVelocity, array_1d<double,3>& rResidual) const override;
    
    void AddMassRHS(VectorType& F,
                    const double Density,
                    const array_1d<double, NumNodes>& rShapeFunc,
                    const double Weight,
                    const std::vector<double>& TimeSchemeWeights,
                    const double& DeltaTime,
                    TElementData& rData);

    void AddMomentumRHS(VectorType& F, const double Weight, TElementData& rData);

    void AddProjectionToRHS(VectorType& RHS,
                            const array_1d<double, 3 > & rAdvVel,
                            TElementData& rData,
                            const double TauOne,
                            const double TauTwo,
                            const double Weight,
                            const double DeltaTime = 1.0);

    void CalculateTau(TElementData& rData,
                      const array_1d<double,3> &Velocity,
                      double &TauOne,
                      double &TauTwo);

    void EvaluateTimeDerivativeInPoint(double& rResult,
                                       const Variable< double >& rVariable,
                                       const array_1d< double,  NumNodes >& rN,
                                       const double& DeltaTime,
                                       const std::vector<double>& rSchemeWeigths);

    void GetModifiedConvectionOperator(array_1d< double,  NumNodes >& rResult,
                                       array_1d< double, 3 > & rVelocity,
                                       const double & rVelocityDiv,
                                       const typename TElementData::ShapeFunctionsType& rN,
                                       const typename TElementData::ShapeDerivativesType& rDN_DX);

    void GetAdvectiveVel(array_1d< double, 3 > & rAdvVel,const typename TElementData::ShapeFunctionsType& rN);

    void MassProjTerm(const TElementData& rData, double &rMassRHS) const override;

    void EvaluateGradientOfScalarInPoint(array_1d< double, 3 >& rResult,
                                         const typename TElementData::NodalScalarData& variable,
                                         const typename TElementData::ShapeDerivativesType& rDN_DX) const;

    int Check(const ProcessInfo &rCurrentProcessInfo) override;

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    std::string Info() const override;


    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const override;


    ///@}
    ///@name Friends
    ///@{


    ///@}

protected:

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
    void AddVelocitySystem(TElementData& rData, MatrixType &rLocalLHS, VectorType &rLocalRHS) override;

    // Protected interface of FluidElement ////////////////////////////////////

    /**
     * @brief EffectiveViscosity Evaluate the total kinematic viscosity at a given integration point.
     * This function is used to implement Smagorinsky type LES or non-Newtonian dynamics in derived classes.
     * @param rData TElementData instance with information about nodal values
     * @param ElemSize Characteristic length representing the element (for Smagorinsky, this is the filter width)
     * @return Kinematic viscosity at the integration point.
     */
    void GetEffectiveViscosity(TElementData& rData, double& rViscosity);

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
    ///@name Serialization
    ///@{

    friend class Serializer;

    void save(Serializer& rSerializer) const override;

    void load(Serializer& rSerializer) override;

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

    /// Assignment operator.
    QSVMSDEMCoupled& operator=(QSVMSDEMCoupled const& rOther);

    /// Copy constructor.
    QSVMSDEMCoupled(QSVMSDEMCoupled const& rOther);
    ///@}


}; // Class QSVMSDEMCoupled

///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{


/// input stream function
template< class TElementData >
inline std::istream& operator >>(std::istream& rIStream,
                                 QSVMSDEMCoupled<TElementData>& rThis)
{
    return rIStream;
}

/// output stream function
template< class TElementData >
inline std::ostream& operator <<(std::ostream& rOStream,
                                 const QSVMSDEMCoupled<TElementData>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}

///@} // Fluid Dynamics Application group

} // namespace Kratos.

#endif // KRATOS_QSVMS_DEM_COUPLED_H