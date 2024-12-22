/*
 * @Author: LeiJiulong
 * @Date: 2024-12-22 16:59:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-22 17:13:25
 * @Description: 
 * 
 */
#include "CTPmd.h"
#include<fstream>


extern int iInstrumentID;
extern char **ppInstrumentID ;

CTPDataGet::CTPDataGet()
{
    std::cout << "初始化用户信息" << std::endl;
    pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
    strcpy(loginReq.BrokerID, "9999");
    strcpy(loginReq.UserID, "202585");
    strcpy(loginReq.Password, "Jianchi123@");
}

CTPDataGet::~CTPDataGet()
{
}

void CTPDataGet::begin()
{
    char gTradeFrontAddr[] = "tcp://180.168.146.187:10211"; //第一套
    pUserApi->RegisterSpi(this);
    pUserApi->RegisterFront(gTradeFrontAddr);
    
    pUserApi->Init();
    pUserApi->Join();
}

bool CTPDataGet::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    // 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		std::cout << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	return bResult;
}

void CTPDataGet::OnFrontConnected()
{
    std::cout << "onFrontConnected:开始建立连接  " << std::endl;
    int rt = pUserApi->ReqUserLogin(&loginReq, ++requestID);
	std::cout  << "--->>> 发送用户登录请求: " << ((0==rt) ? "成功" : "失败");
}

void CTPDataGet::OnFrontDisconnected(int nReason)
{
    std::cout << "推出登陆 错误码：" << nReason << std::endl;
}

void CTPDataGet::OnHeartBeatWarning(int nTimeLapse)
{
}

void CTPDataGet::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		std::cout << "登陆响应。。。。" << "" << pUserApi->GetTradingDay() << std::endl;
        int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
        std::cout << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << std::endl;
	}
}

void CTPDataGet::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "退出登陆" << std::endl;
}

void CTPDataGet::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout <<"错误码： " << pRspInfo->ErrorID <<"   错误信息："<<pRspInfo->ErrorMsg << std::endl;
}

void CTPDataGet::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====订阅行情成功=====" << std::endl;
		std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
		// 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储
		char filePath[100] = {'\0'};
		sprintf(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
		std::ofstream outFile;
		outFile.open(filePath, std::ios::app); // 新开文件
		outFile << "合约代码" << ","
			<< "UpdateTime" << ","
			<< "LastPrice" << ","
			<< "Volume" << ","

			<< "BidPrice1" << ","
			<< "BidVolume1" << ","
			<< "AskPrice1" << ","
			<< "AskVolume1" << ","

			// << "BidPrice2" << ","
			// << "BidVolume2" << ","
			// << "AskPrice2" << ","
			// << "AskVolume2" << ","

			// << "BidPrice3" << ","
			// << "BidVolume3" << ","
			// << "AskPrice3" << ","
			// << "AskVolume3" << ","

			// << "BidPrice4" << ","
			// << "BidVolume4" << ","
			// << "AskPrice4" << ","
			// << "AskVolume4" << ","

			// << "BidPrice5" << ","
			// << "BidVolume5" << ","
			// << "AskPrice5" << ","
			// << "AskVolume5" << ","
	

			<< "OpenInterest" << ","
			<< "Turnover"
			<< std::endl;
		outFile.close();
	}
	std::cout << "  " << pSpecificInstrument->InstrumentID << std::endl;
}

void CTPDataGet::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "OnRspUnSubMarketData" << std::endl;
}

void CTPDataGet::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    char filePath[100] = {'\0'};
	sprintf(filePath, "%s_market_data.csv", pDepthMarketData->InstrumentID);
	std::ofstream outFile;
	outFile.open(filePath, std::ios::app); // 文件追加写入 
	outFile << pDepthMarketData->InstrumentID << "," 
		<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << "," 
		<< pDepthMarketData->LastPrice << "," 
		<< pDepthMarketData->Volume << "," 

		<< pDepthMarketData->BidPrice1 << "," 
		<< pDepthMarketData->BidVolume1 << "," 
		<< pDepthMarketData->AskPrice1 << "," 
		<< pDepthMarketData->AskVolume1 << "," 

		// << pDepthMarketData->BidPrice2 << "," 
		// << pDepthMarketData->BidVolume2 << "," 
		// << pDepthMarketData->AskPrice2 << "," 
		// << pDepthMarketData->AskVolume2 << "," 

		// << pDepthMarketData->BidPrice3 << "," 
		// << pDepthMarketData->BidVolume3 << "," 
		// << pDepthMarketData->AskPrice3 << "," 
		// << pDepthMarketData->AskVolume3 << "," 

		// << pDepthMarketData->BidPrice4 << "," 
		// << pDepthMarketData->BidVolume4 << "," 
		// << pDepthMarketData->AskPrice4 << "," 
		// << pDepthMarketData->AskVolume4 << "," 

		// << pDepthMarketData->BidPrice5 << "," 
		// << pDepthMarketData->BidVolume5 << "," 
		// << pDepthMarketData->AskPrice5 << "," 
		// << pDepthMarketData->AskVolume5 << "," 

		<< pDepthMarketData->OpenInterest << "," 
		<< pDepthMarketData->Turnover << std::endl;
	outFile.close();
}

void CTPDataGet::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPDataGet::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
