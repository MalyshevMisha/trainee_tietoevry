#include<gtest/gtest.h>
#include<gtest/gtest.h>
#include"NetConfAgentMock.hpp"
#include"MobileClient.hpp"
#include"PathGenerator.hpp"

namespace mock
{

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgReferee;

//parh strings
const std::string _MODEL_NAME("newCommutator");

const std::string _NUMBER_PATH_1 = "/newCommutator:user/subscribers/subscriber[userNumber='1']/userNumber";
const std::string _NAME_PATH_1 = "/newCommutator:user/subscribers/subscriber[userNumber='1']/userName";
const std::string _INCOMING_NUMBER_PATH_1 = "/newCommutator:user/subscribers/subscriber[userNumber='1']/incomingNamber";
const std::string _STATE_PATH_1 = "/newCommutator:user/subscribers/subscriber[userNumber='1']/state";
const std::string _PATH_FOR_SUBSCRIBE_1 = "/newCommutator:user/subscribers/subscriber[userNumber='1']";

const std::string _NUMBER_PATH_2 = "/newCommutator:user/subscribers/subscriber[userNumber='2']/userNumber";
const std::string _NAME_PATH_2 = "/newCommutator:user/subscribers/subscriber[userNumber='2']/userName";
const std::string _INCOMING_NUMBER_PATH_2 = "/newCommutator:user/subscribers/subscriber[userNumber='2']/incomingNamber";
const std::string _STATE_PATH_2 = "/newCommutator:user/subscribers/subscriber[userNumber='2']/state";
const std::string _PATH_FOR_SUBSCRIBE_2 = "/newCommutator:user/subscribers/subscriber[userNumber='2']";

const std::string _USER_NUMBER = "userNumber";
const std::string _INCOMING_NUMBER = "incomingNamber";
const std::string _STATE = "state";

const std::string _IDLE {"idle"};
const std::string _ACTIVE {"active"};
const std::string _BUSY {"busy"};

class MobileClientTest : public ::testing::Test 
{
protected:
  void SetUp() override 
  {
    _NCAmock = std::make_shared<testing::StrictMock<NetConfAgentMock>>();
    EXPECT_CALL(*_NCAmock, initSysrepo()).Times(1);
    _mobC = std::make_unique<mainApp::MobileClient>(_NCAmock);
  }

  void testRegist()
  {
    EXPECT_TRUE(_mobC->setName("1"));
    
    EXPECT_CALL(*_NCAmock, fetchData(_NUMBER_PATH_1, _))
      .WillOnce(Return(false));
    EXPECT_CALL(*_NCAmock, changeData(_NUMBER_PATH_1, "1"))
      .Times(1);
    EXPECT_CALL(*_NCAmock, registerOperData(_MODEL_NAME, _NAME_PATH_1, _))
      .Times(1);
    EXPECT_CALL(*_NCAmock, 
                subscribeForModelChanges(_MODEL_NAME, _PATH_FOR_SUBSCRIBE_1, _))
      .Times(1);
    EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_1, _IDLE))
      .Times(1);
    
    EXPECT_TRUE(_mobC->regist("1"));
  }

  void testCall()
  { 
    EXPECT_CALL(*_NCAmock, fetchData(_STATE_PATH_2, _))
      .WillOnce(DoAll(SetArgReferee<1>(_IDLE), Return(true))); 
    EXPECT_CALL(*_NCAmock,changeData(_STATE_PATH_2, _ACTIVE)).Times(1); 
    EXPECT_CALL(*_NCAmock,changeData(_INCOMING_NUMBER_PATH_2, "1"))
      .Times(1); 
    EXPECT_CALL(*_NCAmock,changeData(_STATE_PATH_1, _ACTIVE)).Times(1);
                         
    EXPECT_TRUE(_mobC->call("2"));
    _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  }

  void testCorrectUnregister()
  {
    EXPECT_CALL(*_NCAmock, removeItem(_PATH_FOR_SUBSCRIBE_1))
      .WillOnce(Return(true));
  }
  
  std::shared_ptr<testing::StrictMock<NetConfAgentMock>> _NCAmock;
  std::unique_ptr<mainApp::MobileClient> _mobC;
  
};

//setName
TEST_F(MobileClientTest, setName) 
{    
  EXPECT_FALSE(_mobC->setName(""));
  EXPECT_TRUE(_mobC->getName().empty());
  EXPECT_TRUE(_mobC->setName("kjbn"));
  EXPECT_EQ(_mobC->getName(), "kjbn");
}

//register
TEST_F(MobileClientTest, nameOrNumberOnRegistIsEmpty) 
{
  EXPECT_FALSE(_mobC->regist(""));
  EXPECT_FALSE(_mobC->regist("1"));
}

TEST_F(MobileClientTest, unableToRegistUserAlreadyExists) 
{ 
  EXPECT_TRUE(_mobC->setName("kjb"));
  EXPECT_CALL(*_NCAmock, 
              fetchData(_NUMBER_PATH_1, _))
    .WillOnce(Return(true));
  EXPECT_FALSE(_mobC->regist("1"));
}

TEST_F(MobileClientTest, unableToRegistIncorrectNumber) 
{ 
  EXPECT_TRUE(_mobC->setName("kjb"));
  EXPECT_FALSE(_mobC->regist("kjb"));
}

TEST_F(MobileClientTest, correctRegist) 
{
  testRegist();
  testCorrectUnregister();
}

//unregister
TEST_F(MobileClientTest, unableToUnregistUserNotCreated) 
{
  EXPECT_FALSE(_mobC->unregist());
}

TEST_F(MobileClientTest, unableToUnregistCanNotRemoveItem) 
{
  testRegist();
  testCall();
  
  _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  EXPECT_FALSE(_mobC->unregist());

  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);
  testCorrectUnregister();
  EXPECT_TRUE(_mobC->unregist()); 
}

TEST_F(MobileClientTest, correctUnregist) 
{
  testRegist();
  testCorrectUnregister();
}

//call
TEST_F(MobileClientTest, unableToMakeCallAnyone) 
{
  testRegist();
  EXPECT_FALSE(_mobC->call(""));
  testCorrectUnregister();
}

TEST_F(MobileClientTest, unableToCallUserNotCreated) 
{
  EXPECT_FALSE(_mobC->call("2"));
}

TEST_F(MobileClientTest, unableToCallWhenYouHaveIncomingCall) 
{
  testRegist();
  _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  EXPECT_FALSE(_mobC->call("4"));
  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);
  testCorrectUnregister();
}

TEST_F(MobileClientTest, unableToCallYourself) 
{
  testRegist();
  EXPECT_FALSE(_mobC->call("1"));
  testCorrectUnregister();
}

TEST_F(MobileClientTest, unableToCallToNotIdleUser) 
{
  testRegist();
  EXPECT_CALL(*_NCAmock, fetchData(_STATE_PATH_2, _))
      .WillOnce(DoAll(SetArgReferee<1>(_ACTIVE), Return(true)));
  EXPECT_FALSE(_mobC->call("2"));
  testCorrectUnregister();
}

TEST_F(MobileClientTest, correctCall) 
{
  testRegist();
  testCall();
  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);
  testCorrectUnregister();
}

//handleModuleChange

//answer
TEST_F(MobileClientTest, unableToMakeAnswerUserIsIdle)
{
  testRegist();
  EXPECT_FALSE(_mobC->answer());
  testCorrectUnregister();
}

TEST_F(MobileClientTest, unableToMakeAnswerUserHasntIncomCall)
{
  testRegist();
  _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  EXPECT_FALSE(_mobC->answer());
  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);
  testCorrectUnregister();
}

TEST_F(MobileClientTest, correctAnswer)
{
  testRegist();
  _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  EXPECT_CALL(*_NCAmock, getOperData(_NAME_PATH_2, _)).Times(1);
  _mobC->handleModuleChange(_INCOMING_NUMBER_PATH_1, "2");
  
  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_2, _BUSY)).Times(1);
  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_1, _BUSY)).Times(1);

  EXPECT_TRUE(_mobC->answer());
  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);
  testCorrectUnregister();
}

//callEnd
TEST_F(MobileClientTest, FailedCallEnd)
{
  testRegist();
  EXPECT_FALSE(_mobC->callEnd());
  testCorrectUnregister();
}

TEST_F(MobileClientTest, callEndAfterIncomingCall)
{
  testRegist();
  _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  EXPECT_CALL(*_NCAmock, getOperData(_NAME_PATH_2, _)).Times(1);
  _mobC->handleModuleChange(_INCOMING_NUMBER_PATH_1, "2");

  _mobC->handleModuleChange(_STATE_PATH_1, _BUSY);

  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_2, _IDLE)).Times(1);
  EXPECT_CALL(*_NCAmock, removeItem(_INCOMING_NUMBER_PATH_1)).Times(1);
  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_1, _IDLE)).Times(1);
  EXPECT_TRUE(_mobC->callEnd());

  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);
  testCorrectUnregister();
}

TEST_F(MobileClientTest, callEndAfterOutgoingCall)
{
  testRegist();
  testCall();

  _mobC->handleModuleChange(_STATE_PATH_1, _BUSY);

  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_2, _IDLE)).Times(1);
  EXPECT_CALL(*_NCAmock, removeItem(_INCOMING_NUMBER_PATH_2)).Times(1);
  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_1, _IDLE)).Times(1);
  EXPECT_TRUE(_mobC->callEnd());

  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);
  testCorrectUnregister();
}

//reject
TEST_F(MobileClientTest, correctReject)
{
  testRegist();
  _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  EXPECT_CALL(*_NCAmock, getOperData(_NAME_PATH_2, _)).Times(1);
  _mobC->handleModuleChange(_INCOMING_NUMBER_PATH_1, "2");

  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_2, _IDLE)).Times(1);
  EXPECT_CALL(*_NCAmock, changeData(_STATE_PATH_1, _IDLE)).Times(1);
  EXPECT_CALL(*_NCAmock, removeItem(_INCOMING_NUMBER_PATH_1)).Times(1);
  EXPECT_TRUE(_mobC->reject());
  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);

  testCorrectUnregister();
}

TEST_F(MobileClientTest, unableToRejectHasntIncomingNumber)
{
  testRegist();
  EXPECT_FALSE(_mobC->reject());
  testCorrectUnregister();
}

TEST_F(MobileClientTest, unableToRejectStateNotActive)
{
  testRegist();
  _mobC->handleModuleChange(_STATE_PATH_1, _ACTIVE);
  EXPECT_CALL(*_NCAmock, getOperData(_NAME_PATH_2, _)).Times(1);
  _mobC->handleModuleChange(_INCOMING_NUMBER_PATH_1, "2");

  _mobC->handleModuleChange(_STATE_PATH_1, _BUSY);

  EXPECT_FALSE(_mobC->reject());
  _mobC->handleModuleChange(_STATE_PATH_1, _IDLE);

  testCorrectUnregister();
}

}