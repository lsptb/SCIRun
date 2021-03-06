#
#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2009 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software.
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

# CMakeLists.txt for Core/Algorithms/Math

SET(Core_Algorithms_Legacy_Math_HEADERS
  share.h
  LinearSystem/AddKnownsToLinearSystem.h
)

SET(Core_Algorithms_Legacy_Math_SRCS
  #AppendMatrix/AppendMatrices.cc
  #AppendMatrix/AppendMatrix.cc
  #CollectMatrices/CollectMatricesAlgorithm.cc
  #ColumnMisfitCalculator/ColumnMatrixMisfitCalculator.cc
  #FindMatrix/FindNonZeroMatrixRows.cc
  #FindMatrix/FindNonZeroMatrixColumns.cc
  #FindMatrix/FindZeroMatrixRows.cc
  #FindMatrix/FindZeroMatrixColumns.cc
  #FindMatrix/FindMatrix.cc
  LinearSystem/AddKnownsToLinearSystem.cc
  #LinearSystem/SolveLinearSystem.cc
  #MappingMatrix/ConvertMappingMatrixIntoMappingOrder.cc
  #MappingMatrix/ConvertMappingOrderIntoMappingMatrix.cc
  #ParallelAlgebra/ParallelLinearAlgebra.cc
  #ReorderMatrix/CutHillMcKee.cc
  #ReorderMatrix/ReverseCutHillMcKee.cc
  #ReorderMatrix/ReorderMatrix.cc
  #RootMeanSquareError/RootMeanSquareError.cc
  #SelectMatrix/SelectSubMatrix.cc
  #SelectMatrix/SelectMatrixRows.cc
  #SelectMatrix/SelectMatrixColumns.cc
  #SelectMatrix/SelectMatrix.cc
  #SetSubMatrix/SetSubMatrix.cc
  #SortMatrix/SortMatrixRows.cc
  #SortMatrix/SortMatrixColumns.cc
  #SortMatrix/SortMatrix.cc
)

SCIRUN_ADD_LIBRARY(Core_Algorithms_Legacy_Math 
  ${Core_Algorithms_Legacy_Math_SRCS}
  ${Core_Algorithms_Legacy_Math_HEADERS}
  )

TARGET_LINK_LIBRARIES(Core_Algorithms_Legacy_Math
  Core_Datatypes
  #Core_Util
  #Core_Exceptions
  #Core_Thread
  #Core_Geom
  #Core_Geometry
  #Core_Persistent
  #Core_Basis
  #Core_Algorithms_Util
  #${SCI_TEEM_LIBRARY}
)

IF(BUILD_SHARED_LIBS)
  ADD_DEFINITIONS(-DBUILD_Core_Algorithms_Legacy_Math)
ENDIF(BUILD_SHARED_LIBS)
