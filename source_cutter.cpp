//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#include "HelpForm.h"
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
   write = false;
   mem = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenClick(TObject *Sender)
{
   if (OpenDialog1->Execute() == ID_OK)
   {
   	file = OpenDialog1->FileName;
      Form1->Caption = "Nif cutter - "+file;
		in = fopen(file.c_str(), "rb");
      file = OpenDialog1->FileName;
		if (!in)
			return ShowMessage ( "Cannot open file.");
      SetBtn->Enabled = true;
      RefreshNum->Visible = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (in)
		fclose(in);
	if (out)
		fclose(out);
   delete []mem;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SetBtnClick(TObject *Sender)
{
	if (in == NULL)
      return;
	nTri = 0;
   nDot = 0;
   pos = Offset->Text.ToInt();
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
   if (nTri > 9000)
   	return;
   Dots->Strings->Clear();
   for (int i = 0; i < nTri; i++)
   {
   	fread(&d, 6, 1, in);
     	Dots->InsertRow(i, IntToStr(d.a)+" "+IntToStr(d.b)+" "+IntToStr(d.c), true);
   }
   RefreshNum->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RefreshClick(TObject *Sender)
{
	struct Data
   {
   	int a : 16;
      int b : 16;
      int c : 16;
   } d;
   int p;
	for (int i = 0; i < Dots->Strings->Count; i++)
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
      if (d.a < 0 || d.b < 0 || d.c < 0)
      {
       	Dots->Cells[1][i] = "";
      	continue;
      }
    	Dots->Cells[1][i] = IntToStr(d.a)+" "+IntToStr(d.b)+" "+IntToStr(d.c);
      if (write)
      	fwrite(&d, 6, 1, out);
   }
   for (int i = 0; i < Dots->Strings->Count; i++)
   {
   	if (Dots->Cells[1][i].IsEmpty())
      {
      	Dots->DeleteRow(i);
         i--;
      }
      else
     		Dots->Cells[0][i] = i;
   }
  	Base->Cells[1][0] = Dots->Strings->Count;
   Base->Cells[1][1] = Dots->Strings->Count * 3;
   Base->Cells[0][0] = "Num Triangles " + IntToStr(nTri)+"(init)";
   Base->Cells[0][1] = "Num Triangle Points " + IntToStr(nDot)+"(init)";
   RefreshNum->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HelpClick(TObject *Sender)
{
	Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BaseSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value)
{
	RefreshNum->Tag = ARow;
 	RefreshNum->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RefreshNumClick(TObject *Sender)
{
 	if (RefreshNum->Tag == 1)
   {
   	int d = Base->Cells[1][1].ToIntDef(-1);
      if (d < 0)
         d = 0;
      if (d % 3 != 0)
       	return ShowMessage("Points should be three times more, than triangles.");
      Base->Cells[1][0] = d / 3;
      SetRowCount(d/3);
      return;
   }
   int d = Base->Cells[1][0].ToIntDef(-1);
   if (d < 0)
   	d = 0;
   Base->Cells[1][0] = d;
   Base->Cells[1][1] = d * 3;
   SetRowCount(d);
}
//---------------------------------------------------------------------------
void TForm1::SetRowCount(int r)
{
	for (int i = Dots->Strings->Count; i < r; i++)
    	Dots->InsertRow(i+1, "0 1 2", true);
   for (int i = Dots->Strings->Count; i > r; i--)
    	Dots->DeleteRow(i-1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveBtnClick(TObject *Sender)
{
   //Base->Cells[1][1] = Dots->RowCount;
   //Base->Cells[1][1] = Base->Cells[1][1] + IntToStr(Dots->Strings->Count);
 	//SetRowCount(Base->Cells[1][0].ToIntDef(0));
   int n = Base->Cells[1][0].ToIntDef(-1);
   int d = Base->Cells[1][1].ToIntDef(-1);
   if (n < 0 || d < 0)
   	return;
   String save = file;
   for (int i = file.Length(); i > 0; i--)
   	if (file[i] == '\\')
      {
         save.Insert("X_", i+1);
         break;
      }
 	out = fopen(save.c_str(), "wb");
   if (out == NULL)
      return ShowMessage("Cannot create nif file.");
   fseek(in, 0, SEEK_END);
   int EoF = ftell(in);
   fseek(in, 0, SEEK_SET);
   Write(pos);
  	fwrite(&n, 2, 1, out);
   fwrite(&d, 4, 1, out);
   write = true;
   RefreshClick(Sender);
   write = false;
   fseek(in, 2+4+nTri*6, SEEK_CUR);
   Write(EoF - ftell(in));
   fclose(out);
   delete []mem;
   mem = NULL;
}
//---------------------------------------------------------------------------
void TForm1::Write(int size)
{
 	static int cap = 65536;
   if (mem == NULL)
   	mem = new byte[cap];
   int Len;
   for (Len = cap; Len < size; Len += cap)
   {
      fread (mem, cap, 1, in);
      fwrite(mem, cap, 1, out);
   }
   Len = size+cap-Len;
   fread (mem, Len, 1, in);
   fwrite(mem, Len, 1, out);
}
//---------------------------------------------------------------------------
