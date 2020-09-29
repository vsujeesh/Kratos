//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Josep Maria Carbonell
//

#if !defined(KRATOS_QUADRILATERAL_GAUSS_LEGENDRE_INTEGRATION_POINTS_H_INCLUDED )
#define  KRATOS_QUADRILATERAL_GAUSS_LEGENDRE_INTEGRATION_POINTS_H_INCLUDED


// System includes

// External includes

// Project includes
#include "integration/quadrature.h"


namespace Kratos
{

class KRATOS_API(KRATOS_CORE) QuadrilateralGaussLegendreIntegrationPoints1
{
public:
    KRATOS_CLASS_POINTER_DEFINITION(QuadrilateralGaussLegendreIntegrationPoints1);
    typedef std::size_t SizeType;

    static const unsigned int Dimension = 2;

    typedef IntegrationPoint<2> IntegrationPointType;

    typedef std::array<IntegrationPointType, 1> IntegrationPointsArrayType;

    typedef IntegrationPointType::PointType PointType;

    static SizeType IntegrationPointsNumber()
    {
        return 1;
    }

    static const IntegrationPointsArrayType IntegrationPoints()
    {
        static const IntegrationPointsArrayType s_integration_points{{
            IntegrationPointType( 0.00 , 0.00 , 4.00 )
        }};
        return s_integration_points;
    }

    std::string Info() const
    {
        std::stringstream buffer;
        buffer << "Quadrilateral Gauss-Legendre quadrature 1 ";
        return buffer.str();
    }
protected:

private:

    static IntegrationPointsArrayType msIntegrationPoints;

}; // Class QuadrilateralGaussLegendreIntegrationPoints1

class KRATOS_API(KRATOS_CORE) QuadrilateralGaussLegendreIntegrationPoints2
{
public:
    KRATOS_CLASS_POINTER_DEFINITION(QuadrilateralGaussLegendreIntegrationPoints2);
    typedef std::size_t SizeType;

    static const unsigned int Dimension = 2;

    typedef IntegrationPoint<2> IntegrationPointType;

    typedef std::array<IntegrationPointType, 4> IntegrationPointsArrayType;

    typedef IntegrationPointType::PointType PointType;

    static SizeType IntegrationPointsNumber()
    {
        return 4;
    }

    static const IntegrationPointsArrayType IntegrationPoints()
    {
        static const IntegrationPointsArrayType s_integration_points{{
            IntegrationPointType( -1.00/std::sqrt(3.0) , -1.00/std::sqrt(3.0), 1.00 ),
            IntegrationPointType(  1.00/std::sqrt(3.0) , -1.00/std::sqrt(3.0), 1.00 ),
            IntegrationPointType(  1.00/std::sqrt(3.0) ,  1.00/std::sqrt(3.0), 1.00 ),
            IntegrationPointType( -1.00/std::sqrt(3.0) ,  1.00/std::sqrt(3.0), 1.00 )
        }};
        return s_integration_points;
    }

    std::string Info() const
    {
        std::stringstream buffer;
        buffer << "Quadrilateral Gauss-Legendre quadrature 2 ";
        return buffer.str();
    }
protected:

private:

    static IntegrationPointsArrayType msIntegrationPoints;

}; // Class QuadrilateralGaussLegendreIntegrationPoints2

class KRATOS_API(KRATOS_CORE) QuadrilateralGaussLegendreIntegrationPoints3
{
public:
    KRATOS_CLASS_POINTER_DEFINITION(QuadrilateralGaussLegendreIntegrationPoints3);
    typedef std::size_t SizeType;

    static const unsigned int Dimension = 2;

    typedef IntegrationPoint<2> IntegrationPointType;

    typedef std::array<IntegrationPointType, 9> IntegrationPointsArrayType;

    typedef IntegrationPointType::PointType PointType;

    static SizeType IntegrationPointsNumber()
    {
        return 9;
    }

    static const IntegrationPointsArrayType IntegrationPoints()
    {
        static const IntegrationPointsArrayType s_integration_points{{
            IntegrationPointType( -std::sqrt(3.00/5.00) , -std::sqrt(3.00/5.00), 25.00/81.00 ),
            IntegrationPointType( 0.00 , -std::sqrt(3.00/5.00), 40.00/81.00 ),
            IntegrationPointType(  std::sqrt(3.00/5.00) , -std::sqrt(3.00/5.00), 25.00/81.00 ),
            IntegrationPointType( -std::sqrt(3.00/5.00), 0.00, 40.00/81.00 ),
            IntegrationPointType( 0.00 , 0.00, 64.00/81.00 ),
            IntegrationPointType( std::sqrt(3.00/5.00), 0.00, 40.00/81.00 ),
            IntegrationPointType( -std::sqrt(3.00/5.00), std::sqrt(3.00/5.00), 25.00/81.00 ),
            IntegrationPointType( 0.00, std::sqrt(3.00/5.00), 40.00/81.00 ),
            IntegrationPointType( std::sqrt(3.00/5.00), std::sqrt(3.00/5.00), 25.00/81.00 )
        }};
        return s_integration_points;
    }

    std::string Info() const
    {
        std::stringstream buffer;
        buffer << "Quadrilateral Gauss-Legendre quadrature 3 ";
        return buffer.str();
    }
protected:

private:

    static IntegrationPointsArrayType msIntegrationPoints;

}; // Class QuadrilateralGaussLegendreIntegrationPoints3

class KRATOS_API(KRATOS_CORE) QuadrilateralGaussLegendreIntegrationPoints4
{
public:
    KRATOS_CLASS_POINTER_DEFINITION(QuadrilateralGaussLegendreIntegrationPoints4);
    typedef std::size_t SizeType;

    static const unsigned int Dimension = 2;

    typedef IntegrationPoint<2> IntegrationPointType;

    typedef std::array<IntegrationPointType, 16> IntegrationPointsArrayType;

    typedef IntegrationPointType::PointType PointType;

    static SizeType IntegrationPointsNumber()    {  return 16; }

    static const IntegrationPointsArrayType IntegrationPoints()
    {
        static const IntegrationPointsArrayType s_integration_points{{
            IntegrationPointType( -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType( -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType( -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType( -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType( -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType( -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType( -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType( -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 + std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), -std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 - 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 + std::sqrt(5.0/6.0)/6.0)),
            IntegrationPointType(  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ),  std::sqrt( (3.0 + 2.0 * std::sqrt(6.0/5.0)) / 7.0 ), (0.5 - std::sqrt(5.0/6.0)/6.0)*(0.5 - std::sqrt(5.0/6.0)/6.0))
        }};
        return s_integration_points;
    }

    std::string Info() const
    {
        std::stringstream buffer;
        buffer << "Quadrilateral Gauss-Legendre quadrature 4 ";
        return buffer.str();
    }
protected:

private:

    static IntegrationPointsArrayType msIntegrationPoints;

}; // Class QuadrilateralGaussLegendreIntegrationPoints4

class KRATOS_API(KRATOS_CORE) QuadrilateralGaussLegendreIntegrationPoints5 {
public:
	KRATOS_CLASS_POINTER_DEFINITION(QuadrilateralGaussLegendreIntegrationPoints5);
	typedef std::size_t SizeType;

	static const unsigned int Dimension = 2;

	typedef IntegrationPoint<2> IntegrationPointType;

	typedef std::array<IntegrationPointType, 25> IntegrationPointsArrayType;

	typedef IntegrationPointType::PointType PointType;

	static SizeType IntegrationPointsNumber() {return 25;}

    static IntegrationPointsArrayType IntegrationPoints()
    {
        static IntegrationPointsArrayType s_integration_points;
        const double a[] = {-0.906179845938664, -0.538469310105683, 0.000000000000000, 0.538469310105683, 0.906179845938664};
        const double w[] = {0.236926885056189, 0.478628670499366, 0.568888888888889, 0.478628670499366, 0.236926885056189};

        for(unsigned int i = 0; i < 5; ++i) {
            for(unsigned int j = 0; j < 5; ++j) {
                s_integration_points[5*i + j] = IntegrationPointType( a[i], a[j], w[i] * w[j]);
            }
        }

        return s_integration_points;
	}

	std::string Info() const
	{
		std::stringstream buffer;
		buffer << "Quadrilateral Gauss-Legendre quadrature 5 ";
		return buffer.str();
	}
protected:

private:

	static IntegrationPointsArrayType msIntegrationPoints;

}; // Class QuadrilateralGaussLegendreIntegrationPoints5


///@name Type Definitions
///@{


///@}
///@name Input and output
///@{


///@}


}  // namespace Kratos.

#endif // KRATOS_QUADRILATERAL_GAUSS_LEGENDRE_INTEGRATION_POINTS_H_INCLUDED  defined


