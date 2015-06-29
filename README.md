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

The `Matrix` object has the following methods:

## addScaledRow

## get

## innerProduct

## scale

## set

## setAll

## setRow

# License
node-gsl-matrix is available under the MIT license.
