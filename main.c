#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9

void setcolor(int ForgC)
{ WORD wColor;
HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
{
	wColor=(csbi.wAttributes & 0xF0)+(ForgC & 0x0F);

	SetConsoleTextAttribute(hStdOut,wColor);

}
}


struct item
{
	char productname[40],productcomp[40],c;
	int productid;
	int price;
	int Qnt;
}st;

void wel_come(void);
void title(void);
void login();
void menu(void);
void title(void);
void deleteproduct(void);
void gotoxy(short x, short y)
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void add_item();
void read_item();
void search_item();
void edit_item();
void main(void)
{
    menu();
}


void menu(void)
{
	int choice;
	system("cls");
	main:
	printf("\n Stock Manager");
	printf("                                                                                            ");
	printf("                                                                                          ");
	printf("\n\t\tPress <1> Ajouter un produit");
	printf("\n\t\tPress <2> Supprimer un produit");
	printf("\n\t\tPress <3> Recherche d'un produit dans le stock");
	printf("\n\t\tPress <4> Read Items");
	printf("\n\t\tPress <5> Modifier un produit");
	printf("\n\t\tPress <6> Exit!");

	printf("\n\n\t\tEntre votre choix[1-6]");
	scanf("%i", &choice);

	system("cls");

	switch(choice)
	{
		case 1:
			add_item();
			break;
		case 2:
			deleteproduct();
			break;
		case 3:
		search_item();
			break;
		case 4:
		read_item();
			break;
		case 5:
			edit_item();
			break;
		case 6:
		printf("Sortie du système ");
		exit(0);
		break;


		default:
		printf(" choix invalide! Sortie du système\n");
			getch();
	}

}

void add_item()
{
	int index, valid;
	char c;
	int a=0;

	FILE *fp;


	do
	{
		system("cls");
		printf("============ Entrez les détails du produit ============");
		int ID;
		fp = fopen("NextFile.dat.dat","a+");

		if((fp = fopen("NextFile.dat.dat","a+"))!=NULL)
		{
			I:
			printf("\nCode produit\t :");
			scanf("%i",&ID);
			while(fscanf(fp,"%s %s %i %i %i", st.productname, st.productcomp, &st.price, &st.productid,&st.Qnt)!=EOF)
			{

				if(ID == st.productid)
				{
					printf("\n\tLE CODE PRODUIT EXISTE DEJA.\n");
					goto I;
				}
			}
			st.productid = ID;
		}
		else
		{
			printf("\n code produit\t :");
			scanf("%i",&st.productid);
		}

		do
		{

			fflush(stdin);
			printf("\n nom produit \t :");
			gets(st.productname);
			st.productname[0]=toupper(st.productname[0]);
			for (index=0; index<strlen(st.productname); ++index)
			{
				if(isalpha(st.productname[index]))
					valid = 1;
				else
				{
					valid = 0;
					break;
				}
			}
			if (!valid)
			{
				printf("\n Le nom contient un caractère non valide. Veuillez 'Entrer' à nouveau");
				getch();


			}
		}while(!valid);



			do
		{
			char productcomp[40];
			fflush(stdin);
			printf("\nProduit Entreprise\t :");
			gets(st.productcomp);
			st.productcomp[0]=toupper(st.productcomp[0]);

			for (index=0; index<strlen(st.productcomp); ++index)
			{
				if(isalpha(st.productcomp[index]))
					valid = 1;
				else
				{
					valid = 0;
					break;
				}
			}
			if (!valid)
			{
				printf("\n Le nom contient un caractère non valide. Veuillez 'Entrer' à nouveau");
				getch();


			}
		}while(!valid);


		do
			{
				printf("\nPrix [10-5000]dinares:");
				scanf("%i",&st.price);
				if(st.price<10 || st.price>5000)
				{
					printf("\n\tVous ne pouvez pas entrer la limite de prix [10-5000]. Entrez à nouveau.");
				}
			}while(st.price<10 || st.price>5000);

				do
			{
				printf("\nQuantite [1-500]\t:");
				scanf("%i",&st.Qnt);
				if(st.Qnt<1 || st.Qnt>500)
				{
					printf("\n\tEntrez la quantité [1-500] uniquement. Entrez à nouveau.");
				}
			}while(st.Qnt<1 || st.Qnt>500);


		fp=fopen("NextFile.dat","a");
		fprintf(fp,"\n%s %s %i %i %i", st.productname, st.productcomp,st.price, st.productid,st.Qnt);
		fclose(fp);
		printf("\nAppuyez sur 'Entrée'  pour ajouter plus d'éléments et toute autre touche pour accéder au menu principal");

	}
	while((c = getch()) =='\r');
	menu();
}


void search_item()
{
	char target[40];
	int found=0;
	FILE *sfile;
	sfile=fopen("NextFile.dat","r");
	printf("\nEntre le nom chercher:");
	fflush(stdin);
	gets(target);
	target[0]=toupper(target[0]);
	while (!feof(sfile) && found==0)
	{
		fscanf(sfile,"%s %s %i %i %i", st.productname, st.productcomp, &st.price, &st.productid,&st.Qnt);
		if(strcmp(target, st.productname)==0)
		{
			found=1;
		}
	}

	if(found)
	{
		printf("\n Record found");
		printf("\nnom produit\t\t:%s  \nProduit Entreprise\t\t:%s \nPrix produit\t\t:%i \n code produit \t\t:%i \nquantite produit\t:%i", st.productname, st.productcomp, st.price, st.productid, st.Qnt);

	}
	else
		printf("Non Enregistrement trouvé");
		fclose(sfile);
		printf("\nPress any key to go to Main Menu!");
		while((st.c = getch()) =='\r');
		menu();

}

void deleteproduct(void)
{
	char target[40];
	int found=0;
	FILE *sfile, *tfile;
	sfile=fopen("fichier suivant.dat","r");
	tfile=fopen("Tempfichier.dat","w+");
	printf("\n entrer nom supprimer: ");
	fflush(stdin);
	scanf("%s",target);
	target[0]=toupper(target[0]);
	while (fscanf(sfile,"%s %s %i %i %i\n",st.productname,st.productcomp, &st.price,&st.productid,&st.Qnt)!=EOF)
	{
		if(strcmp(target,st.productname)==0)
		{
			found=1;
		}
		else
		{
			fprintf(tfile,"%s %s %i %i %i\n", st.productname,st.productcomp, st.price,st.productid,st.Qnt);
		}
	}
			if(!found)
			{

				printf("\n Enregistrement non trouvé");
				getch();
				menu();
			}
			else
			{
				printf("\n Enregistrement supprimer");
			}
			fclose(sfile);
			fclose(tfile);
			remove("NextFile.dat");
			rename("Tempfile.dat","NextFile.dat");

			printf("\nPress any key to go to Main Menu!");
		while((st.c = getch()) =='\r');
		menu();
}

void read_item()
{
	FILE *f;
	int i, q;
	if((f=fopen("NextFile.dat","r"))==NULL)
	{

		gotoxy(10,3);
		printf("NOn enregistrement");
		printf("\n\t\tPress any key to go back to Menu.");
		getch();
		menu();


	}
	else
	{

		gotoxy(0,5);
			for(i=0;i<100;i++)
		{
			printf("-");
		}
		gotoxy(5,6);
		printf("nom produit");
		gotoxy(25,6);
		printf("prix produit");
		gotoxy(40,6);
		printf("entreprise produit");
		gotoxy(60,6);
		printf("code de produit");
		gotoxy(80,6);
		printf("quantite produit\n");

		for(i=0;i<100;i++)
		{
			printf("-");
		}
		q=8;
		while(fscanf(f,"%s %s %i %i %i\n", st.productname,st.productcomp, &st.price, &st.productid,&st.Qnt)!=EOF)
		{
			gotoxy(5,q);
			printf("%s",st.productname);
			gotoxy(25,q);
			printf("%i",st.price);
			gotoxy(40,q);
			printf("%s",st.productcomp);
			gotoxy(60,q);
			printf("%i",st.productid);
			gotoxy(80,q);
			printf("%i",st.Qnt);

			q++;
		}
		printf("\n");
		for(i=0;i<100;i++)
			printf("-");
	}
	fclose(f);

	printf("\nPress any key to go to Main Menu!");
		getch();
		menu();
}

void edit_item()
{
	int index, valid;
	char target[40];
	FILE *fp, *rp;
	int a=0;
	int id;
	char edit;
	long int size=sizeof(st);
	if((fp=fopen("NextFile.dat","r+"))==NULL)
	{
		printf("Non enregistrement ajouter.");
		menu();
	}
	else
	{
		rp = fopen("TempFile.dat","a");
		system("cls");
		printf("Entrer code produit editer:");
		scanf("%i",&id);
		fflush(stdin);
		while(fscanf(fp,"%s %s %i %i %i\n", st.productname,st.productcomp, &st.price, &st.productid,&st.Qnt)!=EOF)
		{
			if(id==st.productid)
			{

				a=1;
				printf("\n\t*****  enregistrement trouvé  *****");
				printf("\n nom produit\t\t: %s",st.productname);
				printf("\n entreprise produit\t\t: %s",st.productcomp);
				printf("\nPrix\t\t\t: %i",st.price);
				printf("\n Code\t\t: %i",st.productid);
				printf("\n quantité produit\t:%i",st.Qnt);

				printf("\n\n\t*** nouveau enregistrement ***");
			do
				{

					fflush(stdin);
					printf("\nNom nouveau produit\t\t: ");
					gets(st.productname);
					st.productname[0]=toupper(st.productname[0]);
					for (index=0; index<strlen(st.productname); ++index)
					{
						if(isalpha(st.productname[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Le nom contient un caractère non valide. Veuillez 'Entrer' à nouveau");
						getch();


					}
				}while(!valid);



				do
				{
					char productcomp[40];
					fflush(stdin);
					printf("\n entreprise nouveau produit\t\t:");
					gets(st.productcomp);
					st.productcomp[0]=toupper(st.productcomp[0]);
					for (index=0; index<strlen(st.productcomp); ++index)
					{
						if(isalpha(st.productcomp[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Le nom contient un caractère non valide. Veuillez 'Entrer' à nouveau");
						getch();


					}
				}while(!valid);

					do
			{
				printf("\n Nouveau prix [10-5000] dinares:");
				scanf("%i",&st.price);
				if(st.price<10 || st.price>5000)
				{
					printf("\n\t impossible le prix limiter[10-50000], rentrer .");
				}
			}while(st.price<10 || st.price>5000);

				printf("\nEntrer code nouveau produit\t\t:");
				scanf("%i",&st.productid);

				do
			{
				printf("\nNouveau Quantite [1-500]\t:");
				scanf("%i",&st.Qnt);
				if(st.Qnt<1 || st.Qnt>500)
				{
					printf("\n\tEntre nouveau quantite [1-500] .");
				}
			}while(st.Qnt<1 || st.Qnt>500);


				printf("Appuyez sur 'y' pour modifier l'enregistrement existant ou sur n'importe quelle touche pour annuler...");
				edit=getche();
				if(edit=='y' || edit=='Y')
				{
					fprintf(rp,"%s %s %i %i %i\n", st.productname, st.productcomp, st.price, st.productid,st.Qnt);
					fflush(stdin);
					printf("\n\n\t\tVOTRE DOSSIER EST MODIFIÉ AVEC SUCCÈS!!!");
				}
			}
			else
			{
				fprintf(rp,"%s %s %i %i %i\n", st.productname, st.productcomp, st.price, st.productid,st.Qnt);
				fflush(stdin);
			}

		}
		if(!a)
		{
			printf("\n\nCE PRODUIT N'EXISTE PAS!!!!");
		}
		fclose(rp);
		fclose(fp);
		remove("NextFile.dat");
		rename("TempFile.dat","NextFile.dat");
		getch();
	}
	menu();
}
