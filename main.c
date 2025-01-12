////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

void lireProduits()
{	
	int ref;
	float pu;
	char chaine[TAILLE];
	char produit[TAILLE];

	FILE *f;
	f=fopen("produits.txt","r");

	do
	{
		fread(&produit,sizeof(int),0,f);
		fscanf(f ,"%d %s %f",&ref,chaine,&pu);

		printf("%d %s %.2f\n",ref,chaine,pu);
	} while (fgets(chaine, 80, f) != NULL);

	fclose(f);

}

void lireCommande(FILE *commande,char *NNNN)
{
	int ref = 0 , refcommande;
	int qte;
	float total = 0 ;
	float pu;

	char chaine[TAILLE];
	char produit[TAILLE];
	char produit1[TAILLE];
	char fac[TAILLE] = "facture";

	char nom[TAILLE];

	FILE *prod;
	prod=fopen("produits.txt","r");

	FILE *facture = NULL;

	strcpy(fac,"./factures/facture");
	strcat(fac,NNNN);
	strcat(fac,".txt");

	facture=fopen(fac,"w");

	fread(&produit,TAILLE,0,commande);
	fscanf(commande,"%s",nom);

	fprintf(facture, "Client : %s\n",nom);

	do
	{
		fread(&produit,sizeof(int),0,commande);
		fscanf(commande ,"%d %d",&refcommande ,&qte);

		while(refcommande!=ref)
		{
			fread(&produit1,strlen(produit1),0,prod);
			fscanf(prod,"%d %s %f",&ref,chaine,&pu);

	 	}

		fprintf(facture, "%d %s (PU = %f€) :: %f€\n", qte , chaine , pu, qte*pu);
		total = total + qte*pu;
	} while (fgets(chaine, 80, commande) != NULL);
	
	fprintf(facture, "\n \t\tTotal = %f€", total);

	fclose(commande);
	fclose(prod);
	fclose(facture);
}

void lireCommandeAvecStock(FILE *commande,char *NNNN)
{
	int ref = 0 , refcommande , refstock;
	int qte ,qtestock;
	float total = 0 ;
	float pu;

	char chaine[TAILLE];
	char produit[TAILLE];
	char produit1[TAILLE];
	char fac[TAILLE];
	char testStock[TAILLE]="ToutCommande.txt";

	char nom[TAILLE];

	FILE *prod;
	prod=fopen("produits.txt","r");

	FILE *stock;
	stock=fopen("stock.txt","r");

	FILE *newstock = NULL;
	newstock=fopen(testStock,"a");

	FILE *facture = NULL;

	strcpy(fac,"./factures/facture");
	strcat(fac,NNNN);
	strcat(fac,".txt");

	facture=fopen(fac,"w");

	fread(&produit,TAILLE,0,commande);
	fscanf(commande,"%s",nom);

	fprintf(facture, "Client : %s\n",nom);
	if (prod!=NULL && stock!=NULL && newstock!=NULL && facture!=NULL)
	{	
		while(fscanf(commande ,"%d %d",&refcommande ,&qte)!=EOF)
		{
			fread(&produit,sizeof(int),0,commande);
			fprintf(newstock, "%d %d \n",refcommande, qte);

			while(refcommande!=ref)
			{
				fread(&produit1,strlen(produit1),0,prod);
				fscanf(prod,"%d %s %f",&ref,chaine,&pu);

			}
			while(refstock!=ref)
			{
				fread(&produit1,strlen(produit1),0,stock);
				fscanf(stock,"%d %d",&refstock,&qtestock);
			}
			
			fprintf(facture, "%d %s (PU = %.2f€) :: %.2f€\n", qte , chaine , pu, qte*pu);
			total = total + qte*pu;
		}
	}
	fprintf(facture, "\n \t\tTotal = %.2f€", total);

	fclose(stock);
	fclose(newstock);
	fclose(commande);
	fclose(prod);
	fclose(facture);
}

void verifierStock()
{
	FILE *alerte = NULL;
	alerte = fopen("alerte.txt","w");
	
	FILE *stock = NULL;
	stock = fopen("stock.txt","r");

	FILE *newStock = NULL;
	newStock = fopen("newStock.txt","w");

		int ref = 0 , refcommande , refstock;
		int qte ,qtestock;
		int i = 0;
		float total = 0 ;
		float pu;
		char chaine[TAILLE];
		char produit[TAILLE];
		char produit1[TAILLE];
		char fac[TAILLE];
		char testStock[TAILLE]="ToutCommande.txt";

	while(fscanf(stock ,"%d %d",&refstock ,&qtestock)!= EOF)
	{
		FILE *commande = NULL;
		commande = fopen("ToutCommande.txt","r");
		fread(&produit,sizeof(int),0,commande);
		while(fscanf(commande,"%d %d",&refcommande,&qte)!= EOF)
			{
				if (refstock == refcommande)
				{
					qtestock = qtestock-qte;
				}
				fread(&produit1,strlen(produit1),0,commande);
			}
		if (qtestock <= 0 )
			{
				i++;
				fprintf(alerte,"pas de stock sur le produit : %d, qty : %d \n",refstock,qtestock);
			}
		fclose(commande);
		fprintf(newStock,"%d %d \n",refstock,qtestock);
	}
	fclose(stock);
	fclose(newStock);
	fclose(alerte);
	if (i==0)
	{
		remove("alerte.txt");
	}
	remove("ToutCommande.txt");
	remove("stock.txt");
	rename("newStock.txt","stock.txt");
}

void initStock()
{
	FILE *f;
	f = fopen("stock.txt","w");

	fprintf(f,"123548796 100\n132547896 1000\n132658974 500\n132569874 850\n231546987 790\n231547896 1500\n213456987 2000\n231698547 5000\n321469785 150\n312589647 600\n312698547 1000\n321789654 1200");
	fclose(f);
	printf("Votre stock a bel et bien était rénitialisé !!!\n");
}

int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
	FILE *f;
	int N;
	f=fopen("nextFact","r");
	fread(&N,sizeof(int),1,f);
	fclose(f);
	//printf("\n--->lu N=%d",N);
	return N;
}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
	int m,c,d,u;
	char cm,cc,cd,cu;
	m=N/1000;cm=48+m;
	N%=1000;
	c=N/100;cc=48+c;
	N%=100;
	d=N/10;cd=48+d;
	u=N%10;
	cu=48+u;
	N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}

void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
	FILE *ficCommande=NULL;
	int FINI=0;
	int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
	char NNNN[5];
	char nomCommande[29];

	do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
		{
		strcpy(nomCommande,"./commandes/commande");
		convertirNenChaine4(N,NNNN); 
		printf("\n==>%s<==",NNNN);
		ficCommande=NULL;
		strcat(nomCommande,NNNN);
		strcat(nomCommande,".txt");
		
		printf("\n traitement de  %s",nomCommande);
		
		ficCommande=fopen(nomCommande,"rt");
		if (ficCommande!=NULL)
			{ // le fichier commandeNNNN.txt existe
				printf("\n fichier %s present",nomCommande);
				// lireCommande(ficCommande,NNNN); // à vous de coder cette fonction lors de ce TP9
				lireCommandeAvecStock(ficCommande,NNNN);
				fclose(ficCommande);	
				verifierStock();
			}
		else
			{
				printf("\n toutes les commandes presentes ont ete traitees.");
				FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
				// pour 
				fwrite(&N,1,sizeof(int),f);
				fclose(f);
				FINI=1;			
			}
		N++;
		}while(FINI==0);		

}

int main()
{
	char choix;
	char ch;
	char cho;
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	printf("Voulez vous remettre à 1 NextFact (y/n)? ");
	scanf("%c",&ch);
	if(ch =='y')
	{
		FILE *f;int N=1;
		f=fopen("nextFact","w");
		fwrite(&N,1,sizeof(int),f);
		fclose(f);
	}
	fflush(stdin);

	printf("Voulez vous réinitialiser le stock? (y/n)? ");
	scanf("%c",&choix);
	if(choix=='y')
	{
		initStock();	
	}

	fflush(stdin);
	
	printf("Voulez vous voir le catalogue de produits. (y/n)? ");
	scanf("%c",&cho);
	if(cho == 'y')
	{
		lireProduits();	
	}
	fflush(stdin);

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	//PARTIE 2 du TP : avec Gestion de stock
	printf("\n------- PARTIE 2 -------\n");
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 
	return 0;
}
