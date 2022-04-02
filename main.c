////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

void lireProduits()
{	
	int ref;
	float pu;
	char chaine[50];
	char produit[50];

	FILE *f;
	f=fopen("produits.txt","r");

	do
	{
		fread(&produit,sizeof(int),0,f);
		fscanf(f ,"%d %s %f",&ref,chaine,&pu);

		printf("%d %s %f\n",ref,chaine,pu);
	} while (fgets(chaine, 80, f) != NULL);

	fclose(f);

}

void lireCommande(FILE *commande,char *NNNN)
{
	int ref = 0 , refcommande;
	int qte;
	float total = 0 ;
	float pu;

	char chaine[50];
	char produit[50];
	char produit1[50];
	char fac[50] = "facture";

	char nom[50];

	FILE *prod;
	prod=fopen("produits.txt","r");

	FILE *facture = NULL;

	strcpy(fac,"./factures/facture");
	strcat(fac,NNNN);
	strcat(fac,".txt");

	facture=fopen(fac,"w");

	fread(&produit,50,0,commande);
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


// void lireCommandeAvecStock(FILE *commande,char *NNNN)
// {
// 	int ref = 0 , refcommande , refstock;
// 	int qte ,qtestock;
// 	float total = 0 ;
// 	float pu;

// 	char chaine[50];
// 	char produit[50];
// 	char produit1[50];
// 	char fac[50] = "facture";

// 	char nom[50];

// 	FILE *prod;
// 	prod=fopen("produits.txt","r");

// 	FILE *stock;
// 	stock=fopen("stock.txt","r");

// 	FILE *newstock;
// 	newstock=fopen("newstock.txt","w");

// 	FILE *facture = NULL;

// 	strcpy(fac,"./factures/facture");
// 	strcat(fac,NNNN);
// 	strcat(fac,".txt");

// 	facture=fopen(fac,"w");

// 	fread(&produit,50,0,commande);
// 	fscanf(commande,"%s",nom);

// 	fprintf(facture, "Client : %s\n",nom);

// 	do
// 	{
// 		fread(&produit,sizeof(int),0,commande);
// 		fscanf(commande ,"%d %d",&refcommande ,&qte);

// 		while(refcommande!=ref)
// 		{
// 			fread(&produit1,strlen(produit1),0,prod);
// 			fscanf(prod,"%d %s %f",&ref,chaine,&pu);

// 	 	}
// 		while(refstock!=ref)
// 		{
// 			fread(&produit1,strlen(produit1),0,stock);
// 			fscanf(stock,"%d %d",&refstock,&qtestock);
// 		}
		
// 		fprintf(newstock, "%d %d",ref ,qtestock-qte);
// 		fprintf(facture, "%d %s (PU = %f€) :: %f€\n", qte , chaine , pu, qte*pu);
// 		total = total + qte*pu;
// 	} while (fgets(chaine, 80, commande) != NULL);
	
// 	fprintf(facture, "\n \t\tTotal = %f€", total);

// 	fclose(stock);
// 	fclose(newstock);
// 	fclose(commande);
// 	fclose(prod);
// 	fclose(facture);
// }

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
		//printf("\n==>%s<==",NNNN);
		ficCommande=NULL;
		strcat(nomCommande,NNNN);
		strcat(nomCommande,".txt");
		
		//printf("\n traitement de  %s",nomCommande);
		
		ficCommande=fopen(nomCommande,"rt");
		if (ficCommande!=NULL)
			{ // le fichier commandeNNNN.txt existe
				printf("\n fichier %s present",nomCommande);
				lireCommande(ficCommande,NNNN); // à vous de coder cette fonction lors de ce TP9
				// lireCommandeAvecStock(ficCommande,NNNN);
				fclose(ficCommande);
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
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	FILE *f;int N=1;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	lireProduits();
	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	

	return 0;
}
