//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#include <vector>
#include <set>
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
		full.clear();
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
	if (nTri > 9000)
		return;
	Dots->Strings->Clear();
	Data t;
	vec.resize(nTri);
	for (int i = 0; i < nTri; i++)
	{
		fread(&t, 6, 1, in);
		Dots->InsertRow(i+1, IntToStr(t.a)+" "+IntToStr(t.b)+" "+IntToStr(t.c), true);
		vec[i] = t;
	}
	RefreshNum->Visible = false;
	full.clear();
}
//---------------------------------------------------------------------------
bool TForm1::StrToVector3(String row, Data &d)
{
	row = row.Trim();
	int p = row.Pos(' ');
	if (p < 1)
		return true;
	d.a = row.SubString(1, p-1).ToIntDef(-1);
	row = row.SubString(p+1, row.Length() - p);
	p = row.Pos(' ');
	if (p < 1)
		return true;
	d.b = row.SubString(1, p-1).ToIntDef(-1);
	row = row.SubString(p+1, row.Length() - p);
	if (row.Length() < 1)
		return true;
	d.c = row.ToIntDef(-1);
	if (d.a < 0 || d.b < 0 || d.c < 0)
		return true;
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshClick(TObject *Sender)
{
	int p;
	vec.clear();
	vec.reserve(Dots->Strings->Count);
	Dots->Strings->BeginUpdate();
	for (int i = 0; i < Dots->Strings->Count; i++)
	{
		Data d;
		if (StrToVector3(Dots->Cells[1][i], d))
		{
			Dots->Cells[1][i] = "";
			continue;
		}
	 	Dots->Cells[1][i] = IntToStr(d.a)+" "+IntToStr(d.b)+" "+IntToStr(d.c);
		if (write)
			fwrite(&d, 6, 1, out);
		vec.push_back(d);
	}
	for (int i = 0; i < Dots->Strings->Count; i++)
	{
		if (Dots->Cells[1][i].IsEmpty())
		{
			Dots->DeleteRow(i);
			i--;
		}
		else
	  		Dots->Cells[0][i] = i+1;
	}
	Dots->Strings->EndUpdate();
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
	vec.resize(d);
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

void __fastcall TForm1::DotsKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_DELETE && Dots->Row >= 0)
		if (FullDelete->Checked)
		{
			unsigned int c = full.size();
			Data del = vec[Dots->Row];
			full.insert(del.a);
			full.insert(del.b);
			full.insert(del.c);
			while (full.size() != c)
			{
				c = full.size();
				for (unsigned int i = 0; i < vec.size(); i++)
					if (full.find((vec[i].a)) != full.end() ||full.find((vec[i].b)) != full.end()
						||full.find((vec[i].c)) != full.end())
					{
						full.insert(vec[i].a);
						full.insert(vec[i].b);
						full.insert(vec[i].c);
						//Memo1->Lines->Append(IntToStr(vec[i].b)+" "+IntToStr(vec[i].c));
					}
			}
			Memo1->Lines->Clear();
			for (std::set<unsigned int>::iterator el = full.begin(); el != full.end(); ++el)
				Memo1->Lines->Append(*el);
			for (int i = 0; i < Dots->Strings->Count; i++)
				if (full.find(vec[i].a) != full.end())
					if (Dots->Cells[0][i].IsEmpty() == false)
						Dots->Strings->Strings[i] = "=----- "+Dots->Cells[1][i];
		}
		else if (Delete->Checked)
		{
			Data del = vec[Dots->Row];
			if (Dots->Strings->Count > (int)vec.size())
			{
				Memo1->Lines->Append(Dots->Strings->Count);
				Memo1->Lines->Append(vec.size());
				return;
			}
			//Memo1->Lines->Append("Del "+IntToStr(Dots->Row)+"="+IntToStr(del.a)+" "+IntToStr(del.b)+" "+IntToStr(del.c));
			for (int i = Dots->Strings->Count; i >= 0 ; i--)
				if (del.Has(vec[i]))
				{
		 //		  Memo1->Lines->Append(IntToStr(i)+":"+Dots->Strings->Strings[i]);
					Dots->Strings->Strings[i] = "	";
					//Dots->DeleteRow(i);
				}
			//RefreshClick(Sender);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Memo1->Lines->Append(IntToStr((int)vec.size())+"<SIZE>"+IntToStr(Dots->RowCount));
	for (unsigned int i = 0; i < vec.size(); i++)
		Memo1->Lines->Append(IntToStr(vec[i].a)+" "+IntToStr(vec[i].b)+" "+IntToStr(vec[i].c));
}
//---------------------------------------------------------------------------


