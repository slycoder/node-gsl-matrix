# node-gsl-matrix

This package exposes matrix functionality provided by [GSL](https://www.gnu.org/software/gsl/). For many applications such as scientific computing, fast matrix operations are critical. By using GSL, we can take advantage of all the heavy lifting done in the library to provide fast matrix operations.

While GSL also provides a variety of other classes (such as vectors, views, etc.) the goal of this library is simplicity. The only type of object exposed is a matrix. Vectors should be represented as matricies with one of the dimensions set to 1.

# Installation

First you'll need to get an installation of GSL.  If you're on OS X, you can just use [brew](http://brew.sh/).  

    brew install gsl
  
Then you should be able to install this package via npm.

    npm install --save node-gsl-matrix

# Usage

The constructor takes as arguments the number of rows and columns.  You should always instantiate objects using this method.

    var Matrix = require('node-gsl-matrix').Matrix;
    var myMatrix = new Matrix(4, 3);  // A 4x3 matrix

Note that the values in the matrix have no guaranteed initialization.  The `Matrix` object has the methods below (all examples presume that `myMatrix` is a 3x3 identity matrix and `otherMatrix` is a 1x3 matrix equal to `[10, 11]`):

## addScaledRow
Adds a scaled row from another matrix to a row of the target matrix.

    // Add first (and only) row of otherMatrix scaled by 2.0 to second row of myMatrix.
    myMatrix.addScaledRow(1, otherMatrix, 0, 2.0);
    myMatrix;  // [[1, 0], [20, 23]]
    
    // Last argument is optional and assumed to be 1 if not provided.
    myMatrix.addScaledrow(1, otherMatrix, 0);
    myMatrix;  // [[1, 0], [10, 12]]
    
    // Third argument is optional and assumed to be 0 if not provided.
    myMatrix.addScaledrow(1, otherMatrix);
    myMatrix;  // [[1, 0], [10, 12]]
    
## get
Return the value in a particular entry

    myMatrix.get(0, 0);  // 1

## innerProduct
Return the inner product of a row in this matrix with a row in another matrix

    // Compute the inner product of the second row of myMatrix 
    // with the first (and only) row of otherMatrix
    myMatrix.innerProduct(1, otherMatrix, 0);   // 11
    
    // Last argument is optional, first row is assumed.
    myMatrix.innerProduct(1, otherMatrix);  // 11

## scale
Multiplies all values in the matrix by a constant value.

    myMatrix.scale(0.1);
    myMatrix;  // [[0.1, 0] [0, 0.1]]

## set
Set a particular entry to a value

    myMatrix.set(0, 1, 8);
    myMatrix;  // [[1, 8], [0, 1]]

## setAll
Sets all values in the matrix to a value

    myMatrix.setAll(7);
    myMatrix;  // [[7, 7], [7, 7]]

## setRow
Sets all values in a particular row to a value

    myMatrix.setRow(0, 6);
    myMatrix;  // [[6, 6], [0, 1]]

# License
node-gsl-matrix is available under the MIT license.
