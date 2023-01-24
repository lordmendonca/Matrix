#include <iostream>
#include "CMatrix.h"

void PrintInvertible(bool result);
void PrintInvertible(bool result)
{
    if(result)
    {
        std::cout << "Matrix is Invertible" << std::endl;
    }
    else
    {
        std::cout << "Matrix is not invertible" << std::endl;
    }
}

int main()
{
    std::cout << "**********************************************************************************" << std::endl;
    std::cout << "*                        start sim                                               *" << std::endl;
    std::cout << "**********************************************************************************" << std::endl;

    CMatrix A(2,3);
    std::cout << "Matrix A : " << std::endl;
    for(uint16_t rowIdx = 0; rowIdx < 2; rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < 3; colIdx++)
        {
            A.setBuffer(rowIdx, colIdx, 1);
            //std::cout << A.getBuffer(rowIdx, colIdx);
            //std::cout << "  " ;
        }
        //std::cout << std::endl;
    }
    
    CMatrix B(2,3);
    std::cout << "Matrix B : " << std::endl;
    for(uint16_t rowIdx = 0; rowIdx < 2; rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < 3; colIdx++)
        {
            B.setBuffer(rowIdx, colIdx, colIdx+rowIdx+1);
            //std::cout << B.getBuffer(rowIdx, colIdx);
            //std::cout << "  " ;
        }
        //std::cout << std::endl;
    }

    CMatrix C;
    C = A + B;
    std::cout << "Matrix C : " << std::endl;
    /*for(uint16_t rowIdx = 0; rowIdx < 2; rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < 3; colIdx++)
        {
            std::cout << C.getBuffer(rowIdx, colIdx);
            std::cout << "  " ;
        }
        std::cout << std::endl;
    }*/

    CMatrix D;
    D = B.matrixTranspose();
    std::cout << "Matrix D : " << std::endl;
    /*for(uint16_t rowIdx = 0; rowIdx < D.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < D.getColumn(); colIdx++)
        {
            std::cout << D.getBuffer(rowIdx, colIdx);
            std::cout << "  " ;
        }
        std::cout << std::endl;
    }*/

    CMatrix E;
    E = A * B.matrixTranspose();
    std::cout << "Matrix E : " << std::endl;
    /*for(uint16_t rowIdx = 0; rowIdx < E.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < E.getColumn(); colIdx++)
        {
            std::cout << E.getBuffer(rowIdx, colIdx);
            std::cout << "  " ;
        }
        std::cout << std::endl;
    }

    bool result = E.isInvertible();
    PrintInvertible(result);*/

    CMatrix F(2,2);
    std::cout << "Matrix F : " << std::endl;
    /*for(uint16_t rowIdx = 0; rowIdx < F.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < F.getColumn(); colIdx++)
        {
            F.setBuffer(rowIdx, colIdx, rowIdx+colIdx);
            std::cout << F.getBuffer(rowIdx, colIdx);
            std::cout << "  " ;
        }
        std::cout << std::endl;
    }
    
    result = F.isInvertible();
    PrintInvertible(result);
    std::cout << "Determinant of F : " << F.determinantOfMatrix(F, F.getRow()) << std::endl;*/

    CMatrix G = (E + F) * F;
    std::cout << "Matrix G : " << std::endl;
    /*for(uint16_t rowIdx = 0; rowIdx < G.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < G.getColumn(); colIdx++)
        {
            std::cout << G.getBuffer(rowIdx, colIdx);
            std::cout << "  " ;
        }
        std::cout << std::endl;
    }

    result = G.isInvertible();
    PrintInvertible(result);
    std::cout << "Determinant of G : " << G.determinantOfMatrix(G, G.getRow()) << std::endl;*/

    CMatrix H(3,3);
    std::cout << "Matrix H : " << std::endl;
    for(uint16_t rowIdx = 0; rowIdx < H.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < H.getColumn(); colIdx++)
        {
            H.setBuffer(rowIdx, colIdx, (rowIdx/(colIdx+1)) + (colIdx/(rowIdx+1)));
            std::cout << H.getBuffer(rowIdx, colIdx);
            std::cout << "  " ;
        }
        std::cout << std::endl;
    }

    bool result = H.isInvertible();
    PrintInvertible(result);
    //std::cout << "Determinant of H : " << H.determinantOfMatrix(H, H.getRow()) << std::endl;
    CMatrix INVH = H.inverseMatrix();
    std::cout << "Matrix INVH : " << std::endl;
    for(uint16_t rowIdx = 0; rowIdx < INVH.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < INVH.getColumn(); colIdx++)
        {
            std::cout << INVH.getBuffer(rowIdx, colIdx);
            std::cout << "      " ;
        }
        std::cout << std::endl;
    }

    //CMatrix I = H * H.inverseMatrix();
    CMatrix I = H/H;
    std::cout << "Identity Matrix I =  H * inverse(H) = H/H: " << std::endl;
    for(uint16_t rowIdx = 0; rowIdx < I.getRow(); rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < I.getColumn(); colIdx++)
        {
            std::cout << I.getBuffer(rowIdx, colIdx);
            std::cout << "      " ;
        }
        std::cout << std::endl;
    }

    std::cout << "**********************************************************************************" << std::endl;
    std::cout << "*                        end sim                                                 *" << std::endl;
    std::cout << "**********************************************************************************" << std::endl;
    return 0;
}
