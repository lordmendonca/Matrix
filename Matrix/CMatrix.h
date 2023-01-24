/*
 * CMatrix.h
 */

#ifndef CKALMANFILTER_H_
#define CKALMANFILTER_H_

#include <iostream>

class CMatrix
{
public:
	typedef enum
	{
		ERROR_INVALIDINDEX = -1,
		ERROR_ADDITIONDIMENSIONMISMATCH = -2,
		ERROR_SUBTRACTIONDIMENSIONMISMATCH = -3,
		ERROR_MULTIPLICATIONDIMENSIONMISMATCH = -4,
		ERROR_COFACTORMATRIXDIMENSIONMISMATCH = -5,
		ERROR_DETERMINANTDIMENSIONMISMATCH = -6,
		ERROR_ISINVERTIBLE = -7,
		ERROR_ADJOINTMATRIXDIMENSIONMISMATCH = -8,
		ERROR_DIVIDEBYZERO = -9,
		ERROR_INVERSEMATRIX = -10
	} matrix_st;
private:
	uint16_t	m_row;
	uint16_t	m_column;
	uint16_t	m_size;
	float*		m_buffer;

/**
 * \brief Helper method : matrix index calculation.
 * \param [in] row 		: row index.
 * \param [in] column 	: column index.
 * \return int : It either returns 'INVALID_INDEX' or calculated index position in the matrix.
*/
	int matrixIndexCalc(uint16_t row, uint16_t column) const;

public:
/**
 * \brief Default Constructor
 */
	CMatrix();
/**
 * \brief Parameterized Constructor 
 * \param [in] row 		: row dimension.
 * \param [in] column 	: column dimension.
 */
	CMatrix(uint16_t row, uint16_t column);
/**
 *  \brief Copy Constructor 
 *  \param [in] rho Object reference to the object on the right hand side of the copy operation.
 */
	CMatrix(const CMatrix& rho);
	virtual ~CMatrix();
/**
 * \brief Getter method
 * \return uint16_t : The row dimension of the matrix.
*/
	uint16_t getRow() const;
/**
 * \brief Getter method
 * \return uint16_t : The column dimension of the matrix.
*/
	uint16_t getColumn() const;
/**
 * \brief Getter method
 * \return uint16_t : The size of the matrix.
*/
	uint16_t getSize() const;
/**
 * \brief Getter method
 * \param [in] row 		: row index.
 * \param [in] column 	: column index.
 * \return int : It either returns 'INVALID_INDEX' or value at the indexed position in the matrix.
*/
	float getBuffer(uint16_t row, uint16_t column) const;
/**
 * \brief Setter method
 * \param [in] row 		: row index.
 * \param [in] column 	: column index.
 * \param [in] value 	: value to be stored at the indexed position of the matrix.
 * \return void : no return value.
*/
	void setBuffer(uint16_t row, uint16_t column, float value);
/**
 * \brief Operator Overloading : Overloads the addition operator '+' for objects of type CMatrix.
 * \param [in] rho Object reference to the object on the right hand side of the addition operation.
 * \return Copy of object of type CMatrix.
 */
	CMatrix operator + (const CMatrix& rho);
/**
 * \brief Operator Overloading : Overloads the subtraction operator '-' for objects of type CMatrix.
 * \param [in] rho Object reference to the object on the right hand side of the subtraction operation.
 * \return Copy of object of type CMatrix.
 */
	CMatrix operator - (const CMatrix& rho);
/**
 * \brief Operator Overloading : Overloads the multiplication operator '*' for objects of type CMatrix.
 * \param [in] rho Object reference to the object on the right hand side of the multiplication operation.
 * \return Copy of object of type CMatrix.
 */
	CMatrix operator * (const CMatrix& rho);
/**
 * \brief Operator Overloading : Overloads the multiplication operator '*' for objects of type CMatrix.
 * \param [in] rho Reference to the float on the right hand side of the multiplication operation.
 * \return Copy of object of type CMatrix.
 */
	CMatrix operator * (const float& rho);
/**
 * \brief Operator Overloading : Overloads the division operator '/' for objects of type CMatrix.
 * \param [in] rho Object reference to the object on the right hand side of the division operation.
 * \return Copy of object of type CMatrix.
 */
	CMatrix operator / (const CMatrix& rho);
/**
 * \brief Operator Overloading : Overloads the division operator '/' for objects of type CMatrix.
 * \param [in] rho Reference to the float on the right hand side of the division operation.
 * \return Copy of object of type CMatrix.
 */
	CMatrix operator / (const float& rho);
/**
 * \brief Operator Overloading : Overloads the assignment operator '=' for objects of type CMatrix.
 * \param [in] rho Object reference to the object on the right hand side of the addition operation.
 * \return Reference of object of type CMatrix.
 */
	CMatrix& operator = (const CMatrix& rho);
/**
 * \brief Method to transpose a matrix.
 * \return Copy of object of type CMatrix.
 */	
	CMatrix matrixTranspose();
/**
 * \brief Method to find a cofactor matrix of a matrix.
 * \param [in] mat Object reference to the matrix whose one of the cofactor matrices must be determined.
 * \param [in] rowIdx Row index corresponding to which a cofactor matrix must be determined.
 * \param [in] colIdx Column index corresponding to which a cofactor matrix must be determined.
 * \param [in] dimN Dimension of the matrix whose one of the cofactor matrices must be determined.
 * \return Copy of object of the determined cofactor matrix.
 */	
	CMatrix cofactorMatrix(const CMatrix& mat, uint16_t rowIdxP, uint16_t colIdxQ, uint16_t dimN);
/**
 * \brief Method to find a cofactor matrix of a matrix.
 * \param [in] mat Object reference to the matrix whose determinant msut be calculated.
 * \param [in] dimN Dimension of the matrix whose determinant must be calculated.
 * \return Determinant of the matrix.
 */	
	float determinantOfMatrix(const CMatrix& mat, uint16_t dimN);
/**
 * \brief Method to check if the given matrix is invertible.
 * \return 'true' if invertible, 'false' if not invertible.
 */	
	bool isInvertible();
/**
 * \brief Method to find a cofactor matrix of a matrix.
 * \param [in] mat Object reference to the matrix whose adjoint matrix must be determined.
 * \return Copy of object of the determined adjoint matrix.
 */	
	CMatrix adjointMatrix(const CMatrix& mat);
/**
 * \brief Method to find inverse of a matrix.
 * \return Copy of object of type CMatrix.
 */	
	CMatrix inverseMatrix();
};

#endif /* CMATRIX_H_ */
