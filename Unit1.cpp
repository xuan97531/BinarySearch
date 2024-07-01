//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


struct BSTNode{
	struct BSTNode *leftchild;
	int data;
	struct BSTNode *rightchild;
};

struct DBSTNode{
	struct DBSTNode *leftchild;
	String data;
	int index;
	struct DBSTNode *rightchild;
};

struct BSTNode *root;
struct DBSTNode *Droot;
String tree;
int*X;
int*Y;
int cn;
int**treenode;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*
	�إ߷s�`�I
*/
struct BSTNode *NewBSTNode(int x){
	struct BSTNode*node = new struct BSTNode;
	node->data = x;
	node->leftchild = node->rightchild = NULL;
	return node;
}
//---------------------------------------------------------------------------
/*
	<�D���j>�j�M  p => root
	 1. �� p != NULL (while)
		(1) �j�M�ؼ� x == p->data => return 1 ���ܷj�M���\
		(2) �j�M�ؼ� x  < p->data => p ���ʦ� p->leftchild (���l��)
		(3) �j�M�ؼ� x  > p->data => p ���ʦ� p->rightchild (�k�l��)
	 2. ���j�鵲�� or p == NULL => ���ܷj�M���G or BST���Ū� => return 0

*/
int SearchBST(int x){
	struct BSTNode *p;
	p = root;
	while(p!=NULL){
	   if(x == p->data) return 1;
	   else if(x < p->data) p = p->leftchild;
	   else p = p->rightchild;
	}
	return 0;
}
//---------------------------------------------------------------------------
/*
	<���j>�j�M  node => root
	 1. �� node == NULL => ����BST���Ū� => return 0
	 2. ���j�M�ؼ� x == p->data => return 1 ���ܷj�M���\
		���j�M�ؼ� x  < p->data => return  RSearchBST(node->leftchild,x)(���l��)
		���j�M�ؼ� x  > p->data => return  RSearchBST(node->rightchild,x)(�k�l��)

*/
int RSearchBST(struct BSTNode*node,int x){
	if(node == NULL) return 0;
	else if(x == node->data) return 1;
	else if(x < node->data) return RSearchBST(node->leftchild,x);
	else return RSearchBST(node->rightchild,x);
}
//---------------------------------------------------------------------------
/*
	<���j>�s�W  node => root
	1. �� node == NULL => ����BST���Ū� => return �إߧt�ؼи��X���s�`�I
	2. ���ؼ� x  < p->data => node->leftchild = RInsertBST(node->leftchild,x)(��s���l��)
	   ���ؼ� x  > p->data => node->rightchild = RSearchBST(node->rightchild,x)(��s�k�l��)
	3. return ��s�᪺BST

*/
struct BSTNode* RInsertBST(struct BSTNode* node,int x){
	if(node == NULL) return NewBSTNode(x);
	else if(x < node->data) node->leftchild = RInsertBST(node->leftchild,x);
	else node->rightchild = RInsertBST(node->rightchild,x);
	return node;
}
//---------------------------------------------------------------------------
/*
	<�D���j>�s�W  p => root , q => NULL
	1. �� p != NULL(while) => �����ݷs�W�B
	   (1) q = p => q ���� p �����`�I
	   (2) ���ؼ� x == p->data => return 0 => ����BST���w���ؼ� x ���ݦA�s�W
	   (3) ���ؼ� x  < p->data => p ���ʦ� p->leftchild (���l��)
	   (4) ���ؼ� x  > p->data => p ���ʦ� p->rightchild (�k�l��)
	2.  p = �t�ؼ� x ���s�`�I
	3. �� root == NULL => BST ���Ū� => root = p (�s�Wx�broot)
	4. ���ؼ� x < q->data => �ݷs�W p �b q �����l��
	5. ���ؼ� x > q->data => �ݷs�W p �b q ���k�l��
	6. return 1 => ���ܷs�W���\

*/
int InsertBST(int x){
	struct BSTNode *p,*q;
	p = root, q = NULL;
	while(p!=NULL){
	   q = p;
	   if(x == p->data) return 0;
	   else if(x < p->data) p = p->leftchild;
	   else p = p->rightchild;
	}
	p = NewBSTNode(x);
	if(root == NULL) root = p;
	else if(x < q->data) q->leftchild = p;
	else q->rightchild = p;
	return 1;
}
//---------------------------------------------------------------------------
/*
	<���j>�s�W n �Ӷü�
	1. count => �������\�s�W�üƪ��Ӽ� , list => �������\�s�W���ü�
	2. count < n (while)
	   (1) ���Ͷü� x (rangemin ~ rangemax��)
	   (2) �Y root == NULL(BST����) or BST�������ƪ�
		   <1> (���j)�s�W x
		   <2>  list ���� x
		   <3>  count++
	3. return �s�W�����᪺ root

*/
struct BSTNode* RInsertRandom(int n,int rangemin,int rangemax){
	 int count=0;
	 String list=" => ";
	 Form1->Memo1->Lines->Add("-----(���j)�s�W�üƦ��\("+IntToStr(rangemin)+" ~ "+IntToStr(rangemax)+")------");
	 while(count < n){
		int x = rand()%rangemax+rangemin;
		if(root == NULL || !(SearchBST(x))){
		   root = RInsertBST(root,x);
		   list+=IntToStr(x)+"  ";
		   count++;
		}
	 }
	 Form1->Memo1->Lines->Add(list);
	 return root;
}
//---------------------------------------------------------------------------
/*
	<�D���j>�s�W n �Ӷü�
	1. count => �������\�s�W�üƪ��Ӽ� , list => �������\�s�W���ü�
	2. count < n (while)
	   (1) ���Ͷü� x (rangemin ~ rangemax��)
	   (2) �Y root == NULL(BST����) or BST�������ƪ�
		   <1> (�D���j)�s�W x
		   <2>  list ���� x
		   <3>  count++
	3. return �s�W�����᪺ root

*/
struct BSTNode* InsertRandom(int n,int rangemin,int rangemax){
	 int count=0;
	 String list=" => ";
	 Form1->Memo1->Lines->Add("-----(�D���j)�s�W�üƦ��\("+IntToStr(rangemin)+" ~ "+IntToStr(rangemax)+")------");
	 while(count < n){
		int x = rand()%rangemax+rangemin;
		if(InsertBST(x)){
		   list+=IntToStr(x)+"  ";
		   count++;
		}
	 }
	 Form1->Memo1->Lines->Add(list);
	 return root;
}
//---------------------------------------------------------------------------
/*
	�M��k�l�𤤳̥���
	node => �ݷj�M���k�l�� , p => ���� node ���̥���
*/
struct BSTNode* Right_Left(struct BSTNode*node){
	   struct BSTNode *p;
	   for(p = node; p->leftchild!=NULL; p = p->leftchild);
	   return p;
}
//---------------------------------------------------------------------------
/*
	<���j>�R��
	�ݧR���`�I
		1. ��(214~219,221)
				=> t �����ݧR���`�I => �ݧR���`�I = NULL => �����R�� t
		2. �u���@�l��(214-215,220-221)
				=> t �����ݧR���`�I���l���
				=> t �ҫ�����Ӥl����N�ݧR���`�I��m
				=> �R�� t
		3. ��Ӥl��(225~229)
				=> t �����ݧR���`�I�k�l��̥���
				=> �ݧR���`�I->data ������ t->data
				=> �R���ݧR���`�I�k�l�� t->data ���`�I


*/
struct BSTNode* RDeleteBST(struct BSTNode*node,int x){
	   struct BSTNode *t;
	   if(x < node->data) node->leftchild = RDeleteBST(node->leftchild,x);
	   else if(x > node->data) node->rightchild = RDeleteBST(node->rightchild,x);
	   else{
		  if((node->leftchild == NULL) || (node->rightchild == NULL)){
			 t = (node->leftchild) ? node->leftchild : node->rightchild;
			 if(t == NULL){
				t = node;
				node = NULL;
			 }
			 else *node = *t;
			 free(t);
		  }
		  else{
			 t = Right_Left(node->rightchild);
			 node->data = t->data;
			 node->rightchild = RDeleteBST(node->rightchild,t->data);
		  }
	   }
	   return node;

}
//---------------------------------------------------------------------------
/*
	<�D���j>�R��

*/
int DeleteBST(int x){
	struct BSTNode *p, *pf, *q, *qf;
	p = root; pf = NULL;
	while(p!=NULL){
	   if(x == p->data){
		  if((p->leftchild == NULL) && (p->rightchild == NULL)) q = NULL;
		  else if(p->leftchild!=NULL){
			 qf = p;
			 q  = p->leftchild;
			 while(q->rightchild!=NULL){
				qf = q;
				q  = q->rightchild;
			 }
			 if(p == qf) qf->leftchild = q->leftchild;
			 else qf->rightchild = q->leftchild;
		  }
		  else{
			 qf = p;
			 q  = p->rightchild;
			 while(q->leftchild!=NULL){
				qf = q;
				q  = q->leftchild;
			 }
			 if(p == qf) qf->rightchild = q->rightchild;
			 else qf->leftchild = q->rightchild;
		  }
		  if(q!=NULL){
			 q->leftchild = p->leftchild;
			 q->rightchild = p->rightchild;
		  }
		  if(pf == NULL) root = q;
		  else{
			 if(x < pf->data) pf->leftchild = q;
			 else pf->rightchild = q;
		  }
		  free(p);
		  cn--;
		  return 1;
	   }
	   else{
		  pf = p;
		  if(x < p->data) p = p->leftchild;
		  else p = p->rightchild;
	   }
	}
	return 0;
}
//---------------------------------------------------------------------------
/*
	<���j>���Ǩ��X(LVR)

*/
void printBST_infix(struct BSTNode*node){
	 if(node!=NULL){
		printBST_infix(node->leftchild);
		tree += IntToStr(node->data) + " - ";
		printBST_infix(node->rightchild);
	 }
}
//---------------------------------------------------------------------------
/*
	<���j>�e�Ǩ��X(VLR)

*/
void printBST_prefix(struct BSTNode*node){
	 if(node!=NULL){
		tree += IntToStr(node->data) + " - ";
		printBST_prefix(node->leftchild);
        printBST_prefix(node->rightchild);
	 }
}
//---------------------------------------------------------------------------
/*
	<���j>��Ǩ��X(LRV)

*/
void printBST_postfix(struct BSTNode*node){
	 if(node!=NULL){
		printBST_postfix(node->leftchild);
		printBST_postfix(node->rightchild);
		tree += IntToStr(node->data) + " - ";
	 }
}
//---------------------------------------------------------------------------
/*
	<���j>�M��BST

*/
void ClearBST(struct BSTNode*node){
	 if(node!=NULL){
		ClearBST(node->leftchild);
		ClearBST(node->rightchild);
		DeleteBST(node->data);
	 }
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	 int data = StrToInt(Edit1->Text);
	 if(root == NULL || !(SearchBST(data))){
		root = RInsertBST(root,data);
		tree = "";
		printBST_infix(root);
		Memo1->Lines->Add("-----------(���j)�s�W���\ => �w�s�W "+IntToStr(data)+"--------");
		Memo1->Lines->Add("BST(infix) => "+tree);
	 }
	 else Memo1->Lines->Add("(���j)�s�W���� => BST�w�s�b"+IntToStr(data));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
     int data = StrToInt(Edit1->Text);
	 int suc = InsertBST(data);
	 if(suc){
		tree = "";
		printBST_infix(root);
		Memo1->Lines->Add("-----------(�D���j)�s�W���\ => �w�s�W "+IntToStr(data)+"--------");
		Memo1->Lines->Add("BST(infix) => "+tree);
	 }
	 else Memo1->Lines->Add("(�D���j)�s�W���� => BST�w�s�b"+IntToStr(data));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	 int data = StrToInt(Edit1->Text);
	 if(SearchBST(data)) Memo1->Lines->Add("(�D���j)�j�M���\ => "+IntToStr(data));
	 else{
		// �j�M���G�A�s�W��]
		if(CheckBox2->Checked){
		   Memo1->Lines->Add("(�D���j)�j�M���� => "+IntToStr(data)+"���bBST�� => (�D���j)�s�W�iBST");
		   InsertBST(data);
           tree = "";
		   printBST_infix(root);
		   Memo1->Lines->Add("BST(infix) => "+tree);
		}
		else Memo1->Lines->Add("(�D���j)�j�M���� => "+IntToStr(data)+"���bBST��");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
	 int data = StrToInt(Edit1->Text);
	 if(RSearchBST(root,data))  Memo1->Lines->Add("(���j)�j�M���\ => "+IntToStr(data));
	 else{
		// �j�M���G�A�s�W��]
        if(CheckBox2->Checked){
		   Memo1->Lines->Add("(���j)�j�M���� => "+IntToStr(data)+"���bBST�� => (���j)�s�W�iBST");
		   root = RInsertBST(root,data);
           tree = "";
		   printBST_infix(root);
		   Memo1->Lines->Add("BST(infix) => "+tree);
		}
		else Memo1->Lines->Add("(���j)�j�M���� => "+IntToStr(data)+"���bBST��");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	 int data = StrToInt(Edit1->Text);
	 // ���P�_�ؼ�data �O�_�s�b��BST
	 if(SearchBST(data)){
		root = RDeleteBST(root,data);
		tree = "";
		printBST_infix(root);
		Memo1->Lines->Add("-----------(���j)�R�����\ => �w�R�� "+IntToStr(data)+"--------");
		Memo1->Lines->Add("BST(infix) => "+tree);
	 }
	 else Memo1->Lines->Add("(���j)�R������ => BST�����s�b"+IntToStr(data));

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	 int data = StrToInt(Edit1->Text);
	 int suc = DeleteBST(data);
	 if(suc){
        tree = "";
		printBST_infix(root);
		Memo1->Lines->Add("-----------(�D���j)�R�����\ => �w�R�� "+IntToStr(data)+"--------");
		Memo1->Lines->Add("BST(infix) => "+tree);
	 }
	 else Memo1->Lines->Add("(�D���j)�R������ => BST�����s�b"+IntToStr(data));
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button9Click(TObject *Sender)
{
	 int n = StrToInt(Edit3->Text);
	 int rangemin = StrToInt(Edit2->Text);
	 int rangemax = StrToInt(Edit4->Text);
	 root = RInsertRandom(n,rangemin,rangemax);
	 tree = "";
	 printBST_infix(root);
	 Memo1->Lines->Add("BST(infix) => "+tree);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
	 int n = StrToInt(Edit3->Text);
	 int rangemin = StrToInt(Edit2->Text);
	 int rangemax = StrToInt(Edit4->Text);
	 root  = InsertRandom(n,rangemin,rangemax);
	 tree = "";
	 printBST_infix(root);
	 Memo1->Lines->Add("BST(infix) => "+tree);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
	 tree = "";
	 printBST_prefix(root);
	 Memo1->Lines->Add("�e��(prefix)���XBST------------------------");
	 Memo1->Lines->Add("=> "+tree);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	 tree = "";
	 printBST_infix(root);
	 Memo1->Lines->Add("����(infix)���XBST------------------------");
	 Memo1->Lines->Add("=> "+tree);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
	 tree = "";
	 printBST_postfix(root);
	 Memo1->Lines->Add("���(prefix)���XBST------------------------");
	 Memo1->Lines->Add("=> "+tree);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
	 ClearBST(root);
	 Memo1->Lines->Add("�w�M��BST");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
     Memo1->Clear();
}
//---------------------------------------------------------------------------


