
/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/
 
#include <gtest/gtest.h>

#include <Core/Datatypes/Legacy/Field/VField.h>
#include <Core/Datatypes/Legacy/Field/FieldInformation.h>
#include <Core/Datatypes/Matrix.h>
#include <Core/Algorithms/Legacy/Fields/Mapping/MapFieldDataFromElemToNode.h>
#include <Testing/Utils/SCIRunUnitTests.h>
#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Algorithms/Base/AlgorithmPreconditions.h>
#include <Testing/Utils/MatrixTestUtilities.h>
#include <Core/Datatypes/DenseMatrix.h>

using namespace SCIRun;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Geometry;
using namespace SCIRun::Core::Algorithms::Fields;
using namespace SCIRun::TestUtils;

  
  FieldHandle TetMesh1()
  {     
   return loadFieldFromFile(TestResources::rootDir() / "mapfielddatafrom_/test_mapfielddatafromelemtonode.fld");
  }
  
   FieldHandle TetMesh2()
  {     
   return loadFieldFromFile(TestResources::rootDir() / "mapfielddatafrom_/test_mapfielddatafromnodetoelem.fld");
  } 
  
  DenseMatrixHandle test_mapfielddatafromelemtonodeFLD_IntAvr()
  {
    return MAKE_DENSE_MATRIX_HANDLE(
      (3.5,0)
      (3.5,0)
      (3.33333333333333333333,0)
      (2.0,0)
      (3.5,0)
      (2.5,0)
      (3.8,0)
      (4.33333333333333333333,0));
  } 
  
  DenseMatrixHandle test_mapfielddatafromelemtonodeFLD_Min()
  {
    return MAKE_DENSE_MATRIX_HANDLE(
      (1,0)
      (3,0)
      (2,0)
      (2,0)
      (1,0)
      (1,0)
      (1,0)
      (2,0));
  }

  DenseMatrixHandle test_mapfielddatafromelemtonodeFLD_Max()
  {
    return MAKE_DENSE_MATRIX_HANDLE(
      (6,0)
      (4,0)
      (5,0)
      (2,0)
      (6,0)
      (4,0)
      (6,0)
      (6,0));
  }
  
  DenseMatrixHandle test_mapfielddatafromelemtonodeFLD_Sum()
  {
    return MAKE_DENSE_MATRIX_HANDLE(
      (21,0)
      (7,0)
      (10,0)
      (2,0)
      (7,0)
      (5,0)
      (19,0)
      (13,0));
  }
  
  DenseMatrixHandle test_mapfielddatafromelemtonodeFLD_Med()
  {
    return MAKE_DENSE_MATRIX_HANDLE(
      (4,0)
      (4,0)
      (3,0)
      (2,0)
      (6,0)
      (4,0)
      (4,0)
      (5,0));
  }
  
TEST(MapFieldDataFromElemToNodeAlgoTests, TestNone)
{

 MapFieldDataFromElemToNodeAlgo algo;
 
 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "none");

 FieldHandle input=TetMesh1();
 
 FieldHandle result;
 try
 {
  result = algo.run(input);
 } catch (...) {}
  
 if(result)
 {
   std::cout << " ERROR: THIS MESSAGE SHOULD NOT APPEAR! " << std::endl;
 }
 
}

TEST(MapFieldDataFromElemToNodeAlgoTests, TestNonMethodSpecified)
{

 MapFieldDataFromElemToNodeAlgo algo;
 
 FieldHandle input=TetMesh1();
 
 std::cout << "interpolation/average is default setting" << std::endl;
 
 FieldHandle result = algo.run(input); 
 
 ASSERT_TRUE(result->vfield()->num_values() == 8);
  
 DenseMatrixHandle expected_result = test_mapfielddatafromelemtonodeFLD_IntAvr();
 
 ASSERT_TRUE(expected_result->nrows() == 8);
  
 DenseMatrixHandle output(new DenseMatrix(8, 1));
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 { 
   result->vfield()->get_value((*output)(idx, 0),idx);
 }
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 {
   EXPECT_NEAR((*expected_result)(idx,0),(*output)(idx, 0), 1e-8);
 }
  
}


TEST(MapFieldDataFromElemToNodeTest, TestInterpolate)
{
 
 MapFieldDataFromElemToNodeAlgo algo;

 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "interpolation");
 
 FieldHandle  result = algo.run(TetMesh1());
  
 ASSERT_TRUE(result->vfield()->num_values() == 8);
  
 DenseMatrixHandle expected_result = test_mapfielddatafromelemtonodeFLD_IntAvr();
 
 ASSERT_TRUE(expected_result->nrows() == 8);
  
 DenseMatrixHandle output(new DenseMatrix(8, 1));
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 { 
   result->vfield()->get_value((*output)(idx, 0),idx);
 }
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 {
   EXPECT_NEAR((*expected_result)(idx,0),(*output)(idx, 0), 1e-8);
 }
 
}

TEST(MapFieldDataFromElemToNodeTest, TestAverage)
{
 /// Average and Interpolation option are mapped to the same function
 MapFieldDataFromElemToNodeAlgo algo;

 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "average");
 
 FieldHandle  result = algo.run(TetMesh1());
  
 ASSERT_TRUE(result->vfield()->num_values() == 8);
  
 DenseMatrixHandle expected_result = test_mapfielddatafromelemtonodeFLD_IntAvr();
 
 ASSERT_TRUE(expected_result->nrows() == 8);
  
 DenseMatrixHandle output(new DenseMatrix(8, 1));
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 { 
   result->vfield()->get_value((*output)(idx, 0),idx);
 }
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 {
   EXPECT_NEAR((*expected_result)(idx,0),(*output)(idx, 0), 1e-8);
 }
 
}

TEST(MapFieldDataFromElemToNodeTest, TestMinInterpolation)
{

 MapFieldDataFromElemToNodeAlgo algo;
 
 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "Min");

 FieldHandle  result = algo.run(TetMesh1());

 ASSERT_TRUE(result->vfield()->num_values() == 8);
 
 DenseMatrixHandle output(new DenseMatrix(8, 1));

 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 { 
   result->vfield()->get_value((*output)(idx, 0),idx);
 }
 
 DenseMatrixHandle expected_result_min = test_mapfielddatafromelemtonodeFLD_Min();
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 {
   double tmp = (*expected_result_min)(idx,0);
   EXPECT_NEAR( tmp,(*output)(idx, 0), 1e-16);
 } 
 
}


TEST(MapFieldDataFromElemToNodeTest, TestMaxInterpolation)
{

 MapFieldDataFromElemToNodeAlgo algo;
 
 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "Max");

 FieldHandle  result = algo.run(TetMesh1());

 ASSERT_TRUE(result->vfield()->num_values() == 8);
 
 DenseMatrixHandle output(new DenseMatrix(8, 1));

 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 { 
   result->vfield()->get_value((*output)(idx, 0),idx);
 }
 
 DenseMatrixHandle expected_result_max = test_mapfielddatafromelemtonodeFLD_Max();
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 {
   double tmp = (*expected_result_max)(idx,0);
   EXPECT_NEAR( tmp,(*output)(idx, 0), 1e-16);
 } 
 
}


TEST(MapFieldDataFromElemToNodeTest, TestSumInterpolation)
{

 MapFieldDataFromElemToNodeAlgo algo;
 
 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "Sum");

 FieldHandle  result = algo.run(TetMesh1());

 ASSERT_TRUE(result->vfield()->num_values() == 8);
 
 DenseMatrixHandle output(new DenseMatrix(8, 1));

 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 { 
   result->vfield()->get_value((*output)(idx, 0),idx);
 }
 
 DenseMatrixHandle expected_result_sum = test_mapfielddatafromelemtonodeFLD_Sum();
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 {
   double tmp = (*expected_result_sum)(idx,0);
   EXPECT_NEAR( tmp,(*output)(idx, 0), 1e-16);
 } 
 
}


TEST(MapFieldDataFromElemToNodeTest, TestMedianInterpolation)
{

 MapFieldDataFromElemToNodeAlgo algo;
 
 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "Median");

 FieldHandle  result = algo.run(TetMesh1());

 ASSERT_TRUE(result->vfield()->num_values() == 8);
 
 DenseMatrixHandle output(new DenseMatrix(8, 1));

 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 { 
   result->vfield()->get_value((*output)(idx, 0),idx);
 }
 
 DenseMatrixHandle expected_result_med = test_mapfielddatafromelemtonodeFLD_Med();
 
 for (VMesh::Elem::index_type idx = 0; idx < result->vfield()->num_values(); idx++)
 {
   double tmp = (*expected_result_med)(idx,0);
   EXPECT_NEAR( tmp,(*output)(idx, 0), 1e-16);
 } 
 
}


TEST(MapFieldDataFromElemToNodeAlgoTests, TestDataAlreadyOnNodes)
{

 MapFieldDataFromElemToNodeAlgo algo;
 
 algo.set_option(MapFieldDataFromElemToNodeAlgo::Method, "average");

 FieldHandle input=TetMesh2();

 FieldHandle result;
 try
 {
  result = algo.run(input);
 } catch (...) {}
 
}
