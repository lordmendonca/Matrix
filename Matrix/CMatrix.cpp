/*
 * CMatrix.cpp
 */

#include "CMatrix.h"

CMatrix::CMatrix()
{
    m_row       =   1;
    m_column    =   1;
    m_size      =   m_row * m_column;
    m_buffer    =   new float [m_size];
	for(uint16_t idx = 0; idx < m_size; idx++)
	{
		m_buffer[idx] = 0.0F;
	}
}

CMatrix::CMatrix(uint16_t row, uint16_t column)
{
    m_row       =   row;
    m_column    =   column;
    m_size      =   row * column;
    m_buffer    =   new float [m_size];
	for(uint16_t idx = 0; idx < m_size; idx++)
	{
		m_buffer[idx] = 0.0F;
	}

}

CMatrix::~CMatrix()
{
    delete [] m_buffer;
}

uint16_t CMatrix::getRow() const
{
    return m_row;
}
uint16_t CMatrix::getColumn() const
{
    return m_column;
}
uint16_t CMatrix::getSize() const
{
    return m_size;
}
float CMatrix::getBuffer(uint16_t row, uint16_t column) const
{
    if(matrixIndexCalc(row, column) != CMatrix::ERROR_INVALIDINDEX)
    {
        return m_buffer[matrixIndexCalc(row, column)];
    }
    else
    {
        return (float)CMatrix::ERROR_INVALIDINDEX;
    }
}
void CMatrix::setBuffer(uint16_t row, uint16_t column, float value)
{
    m_buffer[matrixIndexCalc(row, column)] = value;
}

int CMatrix::matrixIndexCalc(uint16_t row, uint16_t column) const
{
	/*	To check indices are out of bound. */
	if (row >= m_row || column >= m_column || row < 0 || column < 0)
	{
		return CMatrix::ERROR_INVALIDINDEX;
	}
	else
	{
		return ((row * m_column) + column);
	}
}

CMatrix::CMatrix(const CMatrix& rho)
{
    this->m_row     = rho.getRow();
    this->m_column  = rho.getColumn();
    this->m_size    = rho.getSize();
    this->m_buffer  = new float[rho.getSize()];

    for(uint16_t rowIdx = 0; rowIdx < this->m_row; rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < this->m_column; colIdx++)
        {
            this->setBuffer(rowIdx, colIdx, rho.getBuffer(rowIdx, colIdx));
        }
    }
}

CMatrix& CMatrix::operator = (const CMatrix& rho)
{
    delete [] this->m_buffer;
    this->m_row     = rho.getRow();
    this->m_column  = rho.getColumn();
    this->m_size    = rho.getSize();
    this->m_buffer  = new float[rho.getSize()];

    for(uint16_t rowIdx = 0; rowIdx < this->m_row; rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < this->m_column; colIdx++)
        {
            this->setBuffer(rowIdx, colIdx, rho.getBuffer(rowIdx, colIdx));
        }
    }
    return *this;
}

CMatrix CMatrix::operator + (const CMatrix& rho)
{
    if((this->m_row == rho.getRow()) && (this->m_column == rho.getColumn()))
    {
        CMatrix temp(this->m_row,this->m_column);
        float sum = 0.0F;
        for(uint16_t rowIdx = 0; rowIdx < this->m_row; rowIdx++)
        {
            for(uint16_t colIdx = 0; colIdx < this->m_column; colIdx++)
            {
                sum = this->getBuffer(rowIdx, colIdx) + rho.getBuffer(rowIdx,colIdx);
                temp.setBuffer(rowIdx, colIdx, sum);
            }
        }
        return temp;
    } 
    else
    {
        std::cout << "Error : Dimension mismatch" << std::endl;
        CMatrix temp(1,1);
        temp.setBuffer(0,0,(float)CMatrix::ERROR_ADDITIONDIMENSIONMISMATCH);
        return temp;
    }
}

CMatrix CMatrix::operator - (const CMatrix& rho)
{
    if((this->m_row == rho.getRow()) && (this->m_column == rho.getColumn()))
    {
        CMatrix temp(this->m_row,this->m_column);
        float diff = 0.0F;
        for(uint16_t rowIdx = 0; rowIdx < this->m_row; rowIdx++)
        {
            for(uint16_t colIdx = 0; colIdx < this->m_column; colIdx++)
            {
                diff = this->getBuffer(rowIdx, colIdx) - rho.getBuffer(rowIdx, colIdx);
                temp.setBuffer(rowIdx, colIdx, diff);
            }
        }
        return temp;
    } 
    else
    {
        std::cout << "Error : Dimension mismatch" << std::endl;
        CMatrix temp(1,1);
        temp.setBuffer(0, 0, (float)CMatrix::ERROR_SUBTRACTIONDIMENSIONMISMATCH);
        return temp;
    }
}

CMatrix CMatrix::operator * (const CMatrix& rho)
{
    
    if(this->m_column == rho.getRow())
    {
        CMatrix temp(this->m_row, rho.getColumn());
        for (uint16_t rowIdx = 0; rowIdx < this->m_row; rowIdx++)
        {
            for (uint16_t colIdx = 0; colIdx < rho.getColumn(); colIdx++)
            {
                temp.setBuffer(rowIdx, colIdx, (float)0.0F);
                float sum = (float) 0.0F;
                for (int k = 0; k < rho.getRow(); k++)
                {
                    sum = temp.getBuffer(rowIdx, colIdx);
                    sum = sum + (this->getBuffer(rowIdx, k) * rho.getBuffer(k, colIdx));
                    temp.setBuffer(rowIdx, colIdx, sum);
                }
            }
        }
        return temp;
    }
    else
    {
        std::cout << "Error : Dimension mismatch" << std::endl;
        CMatrix temp(1,1);
        temp.setBuffer(0, 0, (float)CMatrix::ERROR_MULTIPLICATIONDIMENSIONMISMATCH);
        return temp;
    }
}

CMatrix CMatrix::operator * (const float& rho)
{
        CMatrix temp(this->m_row,this->m_column);
        float product = 0.0F;
        for(uint16_t rowIdx = 0; rowIdx < this->m_row; rowIdx++)
        {
            for(uint16_t colIdx = 0; colIdx < this->m_column; colIdx++)
            {
                product = this->getBuffer(rowIdx, colIdx) * rho;
                temp.setBuffer(rowIdx, colIdx, product);
            }
        }
        return temp;
}

CMatrix CMatrix::operator / (const CMatrix& rho)
{
    if(rho.getRow() == rho.getColumn())
    {
        uint16_t N = rho.getRow();
        CMatrix mat(N, N);
        mat = rho;
        if(mat.isInvertible())
        {
            CMatrix INVMATRIX(N, N);
            // determine inverse matrix of rho (= mat)
            INVMATRIX = mat.inverseMatrix();
            CMatrix quotient;
            // multiply the dividend by reciprocal (= inverse) of divisor
            quotient = *this * INVMATRIX;
            return quotient;
        }
        else
        {
            std::cout << "Error : Matrix is singular and not invertible." << std::endl;
            CMatrix temp(1,1);
            temp.setBuffer(0, 0, CMatrix::ERROR_ISINVERTIBLE);
            return temp;
        }
    }
    else
    {
        std::cout << "ERROR : A non-square matrix cannot be inverted." << std::endl;
        CMatrix temp(1,1);
        temp.setBuffer(0, 0, CMatrix::ERROR_INVERSEMATRIX);
        return temp;
    }
}

CMatrix CMatrix::operator / (const float& rho)
{
    if((float) 0.0F != rho)
    {
        CMatrix temp(this->m_row,this->m_column);
        float quotient = 0.0F;
        for(uint16_t rowIdx = 0; rowIdx < this->m_row; rowIdx++)
        {
            for(uint16_t colIdx = 0; colIdx < this->m_column; colIdx++)
            {
                quotient = this->getBuffer(rowIdx, colIdx) / rho;
                temp.setBuffer(rowIdx, colIdx, quotient);
            }
        }
        return temp;
    }
    else
    {
        std::cout << "Error : Divide bz Zero" << std::endl;
        CMatrix temp(1,1);
        temp.setBuffer(0, 0, (float)CMatrix::ERROR_DIVIDEBYZERO);
        return temp;
    }
}

CMatrix CMatrix::matrixTranspose()
{
    CMatrix temp(this->getColumn(), this->getRow());
    for(uint16_t rowIdx = 0; rowIdx < temp.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < temp.getColumn(); colIdx++)
        {
            temp.setBuffer(rowIdx, colIdx, this->getBuffer(colIdx, rowIdx));
        }
    }
    return temp;
}

CMatrix CMatrix::cofactorMatrix(const CMatrix& mat, uint16_t rowIdxP, uint16_t colIdxQ, uint16_t dimN)
{
    if(mat.getRow() == mat.getColumn())
    {
        CMatrix cofactMatrix(mat.getRow(), mat.getColumn());
        uint16_t i = 0, j = 0;
 
        // Looping for each element of the matrix
        for (uint16_t rowIdx = 0; rowIdx < dimN; rowIdx++)
        {
            for (uint16_t colIdx = 0; colIdx < dimN; colIdx++)
            {
                // Copying into matrix only those element which are not in given row and column
                if (rowIdx != rowIdxP && colIdx != colIdxQ)
                {
                    cofactMatrix.setBuffer(i, j++, mat.getBuffer(rowIdx, colIdx));
 
                    // Row is filled, so increase row index and reset col index
                    if (j == dimN - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return cofactMatrix;
    }
    else
    {
        std::cout << "Error : Dimension mismatch" << std::endl;
        CMatrix temp(1,1);
        temp.setBuffer(0, 0, (float)CMatrix::ERROR_COFACTORMATRIXDIMENSIONMISMATCH);
        return temp;
    }
}

float CMatrix::determinantOfMatrix(const CMatrix& mat, uint16_t dimN)
{
    if(mat.getRow() == mat.getColumn())
    {
        float D = (float) 0.0F; // Initialize determinant
 
        // Base case : if matrix contains single element
        if (dimN == 1)
        {
            return mat.getBuffer(0, 0);
        }

        CMatrix cofactMatrix(mat.getRow(), mat.getColumn()); // To store cofactors
 
        int16_t sign = 1; // To store sign multiplier
 
        // Iterate for each element of first row
        for (uint16_t firstRowIdx = 0; firstRowIdx < dimN; firstRowIdx++)
        {
            // Getting Cofactor of matrix A at row '0' and column 'firstRowIdx'
            cofactMatrix = CMatrix::cofactorMatrix(mat, 0, firstRowIdx, dimN);
            D += sign * mat.getBuffer(0, firstRowIdx) * CMatrix::determinantOfMatrix(cofactMatrix, dimN -1);
            // terms are to be added with alternate sign
            sign = -sign;
        }
 
        return D;
    }
    else
    {
        std::cout << "Error : Dimension mismatch" << std::endl;
        return ((float)CMatrix::ERROR_DETERMINANTDIMENSIONMISMATCH);
    }
}

bool CMatrix::isInvertible()
{
    // Invertible if determinant is not equal to zero.
    if ((float) 0.0F != (float) CMatrix::determinantOfMatrix(*this, this->getRow()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//void adjoint(int A[N][N], int adj[N][N])
CMatrix CMatrix::adjointMatrix(const CMatrix& mat)
{
    if(mat.getRow() == mat.getColumn())
    {
        uint16_t N = mat.getRow();

        if (1 == N)
        {
            CMatrix adj(N, N);
            adj.setBuffer(0, 0, 1);
            return adj;
        }
        // temp is used to store cofactors of A[][]
        int sign = 1;
        CMatrix adjMatrix(N, N);
        CMatrix cofactMatrix(N, N);
 
        for (int rowIdx = 0; rowIdx < N; rowIdx++)
        {
            for (int colIdx = 0; colIdx < N; colIdx++)
            {
                // Get cofactor of matrix A at row 'rowIdx' and column 'colIdx'
                cofactMatrix = CMatrix::cofactorMatrix(mat, rowIdx, colIdx, N);
 
                // sign of adjoint matrix at row 'colIdx' and column 'rowIdx' if sum of row and column indexes is even.
                sign = ((rowIdx + colIdx) % 2 == 0) ? 1 : -1;
 
                // Interchanging rows and columns to get the transpose of the cofactor matrix
                adjMatrix.setBuffer(colIdx, rowIdx, ((sign) * (CMatrix::determinantOfMatrix(cofactMatrix, N-1))));
            }
        }
        return adjMatrix;
    }
    else
    {
        std::cout << "Error : Dimension mismatch" << std::endl;
        CMatrix temp(1,1);
        temp.setBuffer(0, 0, (float)CMatrix::ERROR_ADJOINTMATRIXDIMENSIONMISMATCH);
        return temp;
    }
}

CMatrix CMatrix::inverseMatrix()
{
    uint16_t N = this->getRow();
    float determinant = CMatrix::determinantOfMatrix(*this, N);
    
    CMatrix invMatrix(N, N);
    
    CMatrix adjMatrix(N, N);
    adjMatrix = CMatrix::adjointMatrix(*this);
 
    // Find Inverse Matrix of Matrix A using formula "inverseMatrix(A) = adjointMatrix(A)/determinant(A)"
    for (int rowIdx = 0; rowIdx < N; rowIdx++)
    {
        for (int colIdx = 0; colIdx< N; colIdx++)
        {
            invMatrix.setBuffer(rowIdx, colIdx, (adjMatrix.getBuffer(rowIdx,colIdx)/determinant));
        }
    }
    return invMatrix;
}
