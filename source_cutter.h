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
	TBitBtn *BitBtn2;
	TBitBtn *RefreshNum;
	void __fastcall OpenClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SetBtnClick(TObject *Sender);
	void __fastcall SaveBtnClick(TObject *Sender);
	void __fastcall RefreshClick(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BaseSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall RefreshNumClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
   FILE *in, *out;
   void SetRowCount(int r);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
