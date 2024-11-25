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
	TImage *Image1;
	TButton *Open;
	TButton *Set;
	TOpenDialog *OpenDialog1;
	TValueListEditor *Base;
	TValueListEditor *Dots;
	TButton *Button1;
	TBitBtn *BitBtn1;
	void __fastcall OpenClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SetClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
   FILE *in, *out;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
