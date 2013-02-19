#include "stdafx.h"
#include "Excel.h" 


/******************************************************************************
*
* 这是上面VBAReportDemo的对应程序
* 演示使用VC操作Excel 2003
* 功能：设置单元格，风格，冻结窗格。以及如何将对应的VB代码翻译成VC
*
* 时间：2007-04-16 09:31
* 作者：高宏伟(DukeJoe)
* QQ：21807822
* Blog：http://dukejoe.yeah.net
* 注释：本代码可单独研究，但最好和上面的VBAReportDemo对应看比较好
*
* 开发环境：Visual Studio.NET 2003
* 操作系统：Windows XP Home Edition Service Pack 2
*
*
*****************************************************************************/
/*
#include <iostream>

using namespace std ;

#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE11\mso.dll" rename("RGB", "MSRGB")

#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" raw_interfaces_only, \
	rename("Reference", "ignorethis"), rename("VBE", "JOEVBE")

#import "C:\Program Files\Microsoft Office\OFFICE11\excel.exe" exclude("IFont", "IPicture") \
	rename("RGB", "ignorethis"), rename("DialogBox", "ignorethis"), rename("VBE", "JOEVBE"), \
	rename("ReplaceText", "JOEReplaceText"), rename("CopyFile","JOECopyFile"), \
	rename("FindText", "JOEFindText"), rename("NoPrompt", "JOENoPrompt")

using namespace Office;
using namespace VBIDE;
using namespace Excel ;

int ExportExcelFile() ;

int main(int argc, char* argv[])
{
	if(FAILED(::CoInitialize(NULL)))
		return 1 ;

	ExportExcelFile() ;

	::CoUninitialize();

	return 0;
}

int ExportExcelFile()
{
	_ApplicationPtr pApplication = NULL ;
	_WorkbookPtr pThisWorkbook = NULL ;
	_WorksheetPtr pThisWorksheet = NULL ;
	SheetsPtr pThisSheets = NULL ;
	RangePtr pThisRange = NULL ;
	_variant_t vt ;
	Excel::XlFileFormat vFileFormat ;
	Excel::XlSaveAsAccessMode vSaveAsAccessMode ;
	Excel::XlSaveConflictResolution vSaveConflictResolution ;

	pApplication.CreateInstance("Excel.Application");
	pApplication->PutVisible (0,VARIANT_TRUE);
	pThisWorkbook = pApplication->GetWorkbooks()->Add() ;
	pThisSheets = pThisWorkbook->GetWorksheets() ;
	pThisWorksheet = pThisSheets->GetItem((short)1);
	// 设置整个sheet的填充色为白色
	pThisWorksheet->GetCells()->GetInterior()->PutColor(RGB(255, 255, 255));
	pThisWorksheet->GetCells()->ClearContents() ;
	pThisRange = pThisWorksheet->GetRange("A1:C5") ;
	pThisRange->ClearFormats() ;
	// 如果有不会的，可以在debug文件夹的excel.tlh里找找
	//pThisRange->GetItem(1,1) ;
	pThisRange->PutItem(1, 1, _variant_t("哈尔滨市平房区")) ;
	pThisRange->PutItem(1, 2, _variant_t("高宏伟")) ;
	pThisRange->PutItem(1, 3, _variant_t("QQ:21807822")) ;
	pThisRange->PutItem(2, 1, _variant_t("1")) ;
	pThisRange->PutItem(3, 1, _variant_t("2")) ;
	pThisRange->PutItem(4, 1, _variant_t("3")) ;
	pThisRange->PutItem(5, 1, _variant_t("4")) ;
	// 为Range的四周和内部加上边框
	pThisRange->GetBorders()->GetItem(xlEdgeLeft)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlEdgeTop)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlEdgeRight)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlEdgeBottom)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlInsideHorizontal)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlInsideVertical)->PutLineStyle(xlContinuous) ;
	// 设置第一行的格式（背景色、粗体、颜色、列宽）
	pThisRange->GetRange("A1:C1")->GetInterior()->ColorIndex = 47 ;
	pThisRange->GetRange("A1:C1")->GetInterior()->Pattern = xlPatternSolid ;
	pThisRange->GetRange("A1:C1")->GetFont()->ColorIndex = 6 ;
	pThisRange->GetRange("A1:C1")->GetFont()->Bold = TRUE ;
	pThisRange->GetEntireColumn()->ColumnWidth = 18.63 ;
	pThisRange->GetRange("A2:C5")->GetInterior()->ColorIndex = 16 ;
	pThisRange->GetRange("A2:C5")->GetInterior()->Pattern = xlPatternSolid ;
	pThisRange->GetRange("A2:C5")->GetFont()->ColorIndex = 2 ;
	// 冻结窗格
	pApplication->ActiveWindow->FreezePanes = FALSE ;
	pApplication->Range["A2"]->Select() ;
	pApplication->ActiveWindow->FreezePanes = TRUE ;

	// 存盘退出
	vSaveAsAccessMode = xlNoChange ;
	vFileFormat = xlWorkbookNormal ;
	vSaveConflictResolution = xlLocalSessionChanges ;
	pThisWorkbook->SaveAs(_variant_t("D:\\Visual Studio Projects\\VCReportDemo\\joe.xls"), vFileFormat,_variant_t(""),_variant_t(""), _variant_t(false),
		_variant_t(false), vSaveAsAccessMode, vSaveConflictResolution, _variant_t(false)) ;
	pThisWorkbook->Close();
	pApplication->Quit();

	return 0 ;
}
*/