//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#pragma hdrstop

#include "source_cutter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)	: TForm(Owner)
{
	in = NULL;
	out = NULL;
   OpenDialog1->InitialDir = GetCurrentDir();
   Dots->Strings->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenClick(TObject *Sender)
{
	//String file;
   if (OpenDialog1->Execute() == ID_OK)
   {
		in = fopen(OpenDialog1->FileName.c_str(), "rb"); //_wfopen
   	//in = _wfopen(L"file.bin", Edit1->Text.c_str());
		if (!in)
			return ShowMessage ( "Cannot open file.");
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (in)
		fclose(in);
	if (out)
		fclose(out);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SetClick(TObject *Sender)
{
	if (in == NULL)
      return;
	int nTri = 0;
   int nDot = 0;

   int pos = Offset->Text.ToInt();
  	fseek(in, pos, SEEK_SET);
   fread(&nTri, 2, 1, in);
   fread(&nDot, 4, 1, in);
   Base->Cells[1][0] = nTri;
   Base->Cells[1][1] = nDot;
   struct Data
   {
   	int a : 16;
      int b : 16;
      int c : 16;
   } d;
   if (nTri > 222)
   	return;

   for (int i = 0; i < nTri; i++)
   {
   	fread(&d, 6, 1, in);
     	Dots->InsertRow(i, IntToStr(d.a)+" "+IntToStr(d.b)+" "+IntToStr(d.c), true);
   }
   //->Cells[1][0] = sizeof(d);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	struct Data
   {
   	int a : 16;
      int b : 16;
      int c : 16;
   } d;
   Dots->Cells[1][0] = sizeof(Data);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	struct Data
   {
   	int a : 16;
      int b : 16;
      int c : 16;
   } d;
   int p;
	for (int i = 0; i < Dots->RowCount; i++)
   {
    	String row = Dots->Cells[1][i];
      row = row.Trim();
      p = row.Pos(' ');
      if (p < 1)
      {
       	Dots->Cells[1][i] = "";
      	continue;
      }
      d.a = row.SubString(1, p-1).ToIntDef(-1);
      row = row.SubString(p+1, row.Length() - p);
      p = row.Pos(' ');
      if (p < 1)
      {
       	Dots->Cells[1][i] = "";
      	continue;
      }
      d.b = row.SubString(1, p-1).ToIntDef(-1);
      row = row.SubString(p+1, row.Length() - p);
      if (row.Length() < 1)
      {
       	Dots->Cells[1][i] = "";
      	continue;
      }
      d.c = row.ToIntDef(-1);
      if (d.a < 1 || d.b < 1 || d.c < 1)
      {
       	Dots->Cells[1][i] = "";
      	continue;
      }
      Dots->Cells[1][i] = Dots->Cells[1][i] + ")"+ IntToStr(d.a)+","+IntToStr(d.b)+","+IntToStr(d.c);
   }
   for (int i = 0; i < Dots->RowCount; i++)
   {
   	if (Dots->Cells[1][i].IsEmpty())
      {
      	Dots->DeleteRow(i);
         i--;
      }
      else
     		Dots->Cells[0][i] = i;
   }
}
//---------------------------------------------------------------------------

