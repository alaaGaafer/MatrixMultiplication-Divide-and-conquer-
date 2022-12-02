#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void print(string name, vector<vector<int> > matrix, int n)    //printx the matrices
{
    cout <<name << " = " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
        {
            cout << setw(10) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void add_matrix(vector<vector<int> > matrix_A,vector<vector<int> > matrix_B,vector<vector<int> >& matrix_C,int newSize)  //adds matrices
{
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            matrix_C[i][j]= matrix_A[i][j] + matrix_B[i][j];
}

vector<vector<int> >multiply_matrix(vector<vector<int> > matrix_A,vector<vector<int> > matrix_B)
{
    int n= matrix_A[0].size();                    //since it's n*n matrix then the col = row
    vector<int> result_matrix_row(n, 0);
    vector<vector<int> > matrix_C(n,result_matrix_row);
    if (n == 1)
        matrix_C[0][0]= matrix_A[0][0] * matrix_B[0][0];
    else {
        int newSize = n / 2;                           //dividing the size and the matrices into smaller matrices
        vector<int> row_vector(newSize, 0);
        vector<vector<int> > matrix_C_00(newSize,row_vector);
        vector<vector<int> > matrix_C_01(newSize,row_vector);
        vector<vector<int> > matrix_C_10(newSize,row_vector);
        vector<vector<int> > matrix_C_11(newSize,row_vector);
        vector<vector<int> > a00(newSize, row_vector);
        vector<vector<int> > a01(newSize, row_vector);
        vector<vector<int> > a10(newSize, row_vector);
        vector<vector<int> > a11(newSize, row_vector);
        vector<vector<int> > b00(newSize, row_vector);
        vector<vector<int> > b01(newSize, row_vector);
        vector<vector<int> > b10(newSize, row_vector);
        vector<vector<int> > b11(newSize, row_vector);

        for (int i = 0; i < newSize; i++)               //putting values into the small matrices
            for (int j = 0; j < newSize; j++)
            {
                a00[i][j] = matrix_A[i][j];
                a01[i][j] = matrix_A[i][j + newSize];
                a10[i][j] = matrix_A[newSize + i][j];
                a11[i][j] = matrix_A[i + newSize][j + newSize];
                b00[i][j] = matrix_B[i][j];
                b01[i][j] = matrix_B[i][j + newSize];
                b10[i][j] = matrix_B[newSize + i][j];
                b11[i][j] = matrix_B[i + newSize][j + newSize];
            }
//adding the multiplication of the small matrices and putting them into matrix c
        add_matrix(multiply_matrix(a00, b00),multiply_matrix(a01, b10),matrix_C_00, newSize);
        add_matrix(multiply_matrix(a00, b01),multiply_matrix(a01, b11),matrix_C_01, newSize);
        add_matrix(multiply_matrix(a10, b00),multiply_matrix(a11, b10),matrix_C_10, newSize);
        add_matrix(multiply_matrix(a10, b01),multiply_matrix(a11, b11),matrix_C_11, newSize);

        for (int i = 0; i < newSize; i++)
            for (int j = 0; j < newSize; j++)
            {
                matrix_C[i][j] = matrix_C_00[i][j];
                matrix_C[i][j + newSize] = matrix_C_01[i][j];
                matrix_C[newSize + i][j] = matrix_C_10[i][j];
                matrix_C[i + newSize][j + newSize] = matrix_C_11[i][j];
            }
//clearing the matrices
        matrix_C_00.clear();
        matrix_C_01.clear();
        matrix_C_10.clear();
        matrix_C_11.clear();
        a00.clear();
        a01.clear();
        a10.clear();
        a11.clear();
        b00.clear();
        b01.clear();
        b10.clear();
        b11.clear();
    }
    return matrix_C;
}

int main()
{
    int n=4;                           //size
    vector<vector<int> > matrix_A = { { 1, 2, 3, 4 },
                                      { 5, 6, 7, 8 },
                                      { 9, 1, 2, 3 },
                                      { 4, 5, 6, 7 } };

    print("matrix A", matrix_A, n);

    vector<vector<int> > matrix_B = { { 9, 8, 7, 6 },
                                      { 5, 4, 3, 2 },
                                      { 2, 9, 8, 7 },
                                      { 3, 2, 1, 9 } };

    print("matrix B", matrix_B, n);

    vector<vector<int> > result_matrix(multiply_matrix(matrix_A, matrix_B));
    print("Result matrix", result_matrix,4);
}
//recurrence relation and it's solution.
//T(n) = 7T(n/2)+n^2
//a=7 , b=2 ,f(n)=n^2
//Compare (n^log2 7) with f(n) = n^2
//case 1 applies --> T(n)=Θ(n^log2 7) --> T(n)=o(n^2.81)

