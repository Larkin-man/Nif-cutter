//---------------------------------------------------------------------------

#ifndef source_cutterH
#define source_cutterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *Offset;
	TButton *Open;
	TButton *SetBtn;
	TOpenDialog *OpenDialog1;
	TValueListEditor *Base;
	TValueListEditor *Dots;
	TButton *SaveBtn;
	TBitBtn *Refresh;
	TBitBtn *Help;
	TBitBtn *RefreshNum;
	TMemo *Memo1;
	TButton *Button1;
	TCheckBox *Delete;
	void __fastcall OpenClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SetBtnClick(TObject *Sender);
	void __fastcall SaveBtnClick(TObject *Sender);
	void __fastcall RefreshClick(TObject *Sender);
	void __fastcall HelpClick(TObject *Sender);
	void __fastcall BaseSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall RefreshNumClick(TObject *Sender);
	void __fastcall DotsKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	String file;
	FILE *in, *out;
	void SetRowCount(int r);
	int pos;
	int nTri;
	int nDot;
	bool write;
	byte *mem;
	void Write(int size);
	struct Data
	{
		int a : 16;
		int b : 16;
		int c : 16;
		bool Has(Data rhs)
		{
			return (a==rhs.a||a==rhs.b||a==rhs.c
					||b==rhs.a||b==rhs.b||b==rhs.c
					||c==rhs.a||c==rhs.b||c==rhs.c);
		}
	};
	std::vector<Data> vec;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
