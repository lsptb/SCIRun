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
#include <gmock/gmock.h>
#include <Dataflow/Network/ModuleInterface.h>
#include <Dataflow/Network/Tests/MockNetwork.h>
#include <Dataflow/Engine/Controller/HistoryItem.h>
#include <Dataflow/Engine/Controller/HistoryItemFactory.h>
#include <Dataflow/Engine/Controller/HistoryItemImpl.h>

using namespace SCIRun;
using namespace SCIRun::Dataflow::Engine;
using namespace SCIRun::Dataflow::Networks;
using namespace SCIRun::Dataflow::Networks::Mocks;
using ::testing::_;
using ::testing::Eq;
using ::testing::NiceMock;
using ::testing::DefaultValue;
using ::testing::Return;


class HistoryItemTests : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    DefaultValue<ModuleHandle>::Set(ModuleHandle());
    DefaultValue<ConnectionId>::Set(ConnectionId(""));
    mockNetwork_.reset(new NiceMock<MockNetwork>);
  }
  
  MockNetworkPtr mockNetwork_;
};

TEST_F(HistoryItemTests, CanCreateAddModule)
{
  const std::string name = "ComputeSVD";
  ModuleAddedHistoryItem item(name, NetworkFileHandle());

  EXPECT_EQ("Module Added: " + name, item.name());

  //FAIL();
}

TEST_F(HistoryItemTests, CanCreateRemoveModule)
{
  const std::string name = "ComputeSVD";
  ModuleRemovedHistoryItem item(name, NetworkFileHandle());

  EXPECT_EQ("Module Removed: " + name, item.name());

  //FAIL();
}