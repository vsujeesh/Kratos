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

#if !defined(KRATOS_RANS_EVM_K_EPSILON_K_CROSS_WIND_STABILIZED_ELEMENT_H_INCLUDED)
#define KRATOS_RANS_EVM_K_EPSILON_K_CROSS_WIND_STABILIZED_ELEMENT_H_INCLUDED

// System includes

// External includes

// Project includes
#include "custom_elements/convection_diffusion_reaction_cross_wind_stabilized_element.h"
#include "custom_elements/evm_k_epsilon/evm_k_epsilon_utilities.h"

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

template <unsigned int TDim, unsigned int TNumNodes>
class RansEvmKEpsilonKCrossWindStabilizedElement
    : public ConvectionDiffusionReactionCrossWindStabilizedElement<TDim, TNumNodes, EvmKepsilonModelUtilities::KElementData<TDim>>
{
public:
    ///@name Type Definitions
    ///@{

    using BaseType =
        ConvectionDiffusionReactionCrossWindStabilizedElement<TDim, TNumNodes, EvmKepsilonModelUtilities::KElementData<TDim>>;

    using NodeType = Node<3>;

    using PropertiesType = Properties;

    using GeometryType = Geometry<NodeType>;

    using NodesArrayType = Geometry<NodeType>::PointsArrayType;

    using IndexType = std::size_t;

    ///@}
    ///@name Pointer Definitions
    /// Pointer definition of RansEvmKEpsilonKCrossWindStabilizedElement
    KRATOS_CLASS_POINTER_DEFINITION(RansEvmKEpsilonKCrossWindStabilizedElement);

    ///@}
    ///@name Life Cycle
    ///@{

    /**
     * Constructor.
     */
    explicit RansEvmKEpsilonKCrossWindStabilizedElement(IndexType NewId = 0)
        : BaseType(NewId)
    {
    }

    /**
     * Constructor using an array of nodes
     */
    RansEvmKEpsilonKCrossWindStabilizedElement(IndexType NewId, const NodesArrayType& ThisNodes)
        : BaseType(NewId, ThisNodes)
    {
    }

    /**
     * Constructor using Geometry
     */
    RansEvmKEpsilonKCrossWindStabilizedElement(IndexType NewId, GeometryType::Pointer pGeometry)
        : BaseType(NewId, pGeometry)
    {
    }

    /**
     * Constructor using Properties
     */
    RansEvmKEpsilonKCrossWindStabilizedElement(IndexType NewId,
                                               GeometryType::Pointer pGeometry,
                                               PropertiesType::Pointer pProperties)
        : BaseType(NewId, pGeometry, pProperties)
    {
    }

    /**
     * Copy Constructor
     */
    RansEvmKEpsilonKCrossWindStabilizedElement(RansEvmKEpsilonKCrossWindStabilizedElement const& rOther)
        : BaseType(rOther)
    {
    }

    /**
     * Destructor
     */
    ~RansEvmKEpsilonKCrossWindStabilizedElement() override = default;

    ///@}
    ///@name Operators
    ///@{

    ///@}
    ///@name Operations
    ///@{

    /**
     * creates a new element pointer
     * @param NewId: the ID of the new element
     * @param ThisNodes: the nodes of the new element
     * @param pProperties: the properties assigned to the new element
     * @return a Pointer to the new element
     */
    Element::Pointer Create(IndexType NewId,
                            NodesArrayType const& ThisNodes,
                            PropertiesType::Pointer pProperties) const override
    {
        KRATOS_TRY
        return Kratos::make_intrusive<RansEvmKEpsilonKCrossWindStabilizedElement>(
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
    Element::Pointer Create(IndexType NewId,
                            GeometryType::Pointer pGeom,
                            PropertiesType::Pointer pProperties) const override
    {
        KRATOS_TRY
        return Kratos::make_intrusive<RansEvmKEpsilonKCrossWindStabilizedElement>(
            NewId, pGeom, pProperties);
        KRATOS_CATCH("");
    }

    /**
     * creates a new element pointer and clones the previous element data
     * @param NewId: the ID of the new element
     * @param ThisNodes: the nodes of the new element
     * @param pProperties: the properties assigned to the new element
     * @return a Pointer to the new element
     */
    Element::Pointer Clone(IndexType NewId, NodesArrayType const& ThisNodes) const override
    {
        KRATOS_TRY
        return Kratos::make_intrusive<RansEvmKEpsilonKCrossWindStabilizedElement>(
            NewId, Element::GetGeometry().Create(ThisNodes), Element::pGetProperties());
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
    std::string Info() const override
    {
        std::stringstream buffer;
        buffer << "RansEvmKEpsilonKCrossWindStabilizedElement #" << Element::Id();
        return buffer.str();
    }

    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << "RansEvmKEpsilonKCrossWindStabilizedElement #" << Element::Id();
    }

    /// Print object's data.
    void PrintData(std::ostream& rOStream) const override
    {
        Element::pGetGeometry()->PrintData(rOStream);
    }

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
    ///@name Serialization
    ///@{

    friend class Serializer;

    void save(Serializer& rSerializer) const override
    {
        KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, Element);
    }
    void load(Serializer& rSerializer) override
    {
        KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, Element);
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

}; // Class EvmTurbulentKineticEnergyElement

///@}

///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

template <unsigned int TDim, unsigned int TNumNodes>
inline std::istream& operator>>(std::istream& rIStream,
                                RansEvmKEpsilonKCrossWindStabilizedElement<TDim, TNumNodes>& rThis);

/// output stream function

template <unsigned int TDim, unsigned int TNumNodes>
inline std::ostream& operator<<(std::ostream& rOStream,
                                const RansEvmKEpsilonKCrossWindStabilizedElement<TDim, TNumNodes>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << " : " << std::endl;
    rThis.PrintData(rOStream);
    return rOStream;
}

///@}

} // namespace Kratos.

#endif // KRATOS_RANS_EVM_K_EPSILON_K_CROSS_WIND_STABILIZED_ELEMENT_H_INCLUDED defined
