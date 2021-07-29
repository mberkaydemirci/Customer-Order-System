#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<io.h>
#include<string.h>
#include<stdbool.h>
void yenikayit();
void istenenkayit(int numara);
void bakiyeyenileme();
void hepsiniyazdir();
void isimarama();
void urunkayit();
void musteribilgiguncelleme();
void istenenurun();
void urunbilgiguncelleme();
void urunsiparis();
void faturaolusturma();
struct urun
{
	char kodu[20];
	char isim[10];
	double fiyat;
	int stokmiktari;
}u1;
struct musteri
{
	int hesapNo[100];
	char soyad[20];
	char ad[10];
	double bakiye;
	char telefonNo[13];
	char adres[99];
}m1;
FILE *dosya,*yedek,*urun,*fatura;
int boyut,devam;
bool devamkontrol = false;
bool sipariskontrol = false;
bool yazdirkontrol = false;
int sayac=0,isimaramakontrol,tempmusteri;
char c[20];
void menu()
{		
	int a=0;
	while(a!=-1)
	{   //menunun sürekli ekrana gelmesi ve -1 de çýkýþ yapmasý için
		system("cls");	
		printf("Musteri ve Stok Takip Programi");
		printf("\n 1)Yeni bir musteri kayit:\n 2)Tum musterileri listeleme\n 3)Musteriyi ismine veya isminde gecen harfe "
		"veya heceye gore arama:\n 4)Bir musteriyi, musteri numarasina gore arama\n 5)Musteri kayit guncelleme"
		"(telefon,adres)\n 6)Musteriye bakiye ekleme\n 7)Yeni Urun girisi:\n 8)Bir urunu Urun kodu veya urun ismine gore arama\n"
		" 9)Urunun bilgilerini guncelleme(stok miktari,fiyati)\n 10)Urun siparis\n -1)Cikmak icin \n");
		scanf("%d",&a);
		if(a==1)
		{
			yenikayit();
		}	
		else if(a==2)
		{
			hepsiniyazdir();
		}	
		else if(a==3)
		{
			isimarama();			
		}	
		else if(a==4)
		{
			int numara;
			printf("Musteri numarasi giriniz:");
			scanf("%d",&numara);
			istenenkayit(numara);			
		}
		else if(a==5)
		{
			musteribilgiguncelleme();	
		}
		else if(a==6)
		{
			bakiyeyenileme();
		}
		else if(a==7)
		{
			urunkayit();
		}
		else if(a==8)
		{			
			istenenurun();			
		}
		else if(a==9)
		{
			urunbilgiguncelleme();
		}
		else if(a==10)
		{
			urunsiparis();
		}
		else if(a==-1)
		{
			exit(0);
		}
	}
}
void yenikayit()
{
	int i;
	dosya=fopen( "hesap.dat","rb");
	printf("Hesap No Giriniz:");
	scanf("%d",&m1.hesapNo);
	printf("Ad Giriniz:");
	scanf("%s",m1.ad);
	printf("Soyad Giriniz:");
	scanf("%s",m1.soyad);
	printf("Bakiye Giriniz:");
	scanf("%lf",&m1.bakiye);
	printf("Telefon Numarasi Giriniz:");
	scanf("%s",m1.telefonNo);
	fflush(stdin);
	printf("Adres giriniz:");
	fgets(m1.adres,99,stdin);	
	printf("%d %s %s %f %s %s \n Eklendi",*m1.hesapNo,m1.ad,m1.soyad,m1.bakiye,m1.telefonNo,m1.adres);
	fclose(dosya);
	dosya=fopen( "hesap.dat","ab");
	fwrite(&m1,sizeof(struct musteri),1,dosya);	  //yazdýrýyoruz
	fclose(dosya);
	sayac++;
	printf("\nMenuye donmek icin herhangi bir tusa basin");
	getch();
}

void istenenkayit(int numara)
{ 
	int i =0;
	bool kontrol =false;
	dosya=fopen("hesap.dat","r");
	boyut=filelength(fileno(dosya))/sizeof(struct musteri);	
 	for(i=0;i<boyut;i++)
	 {	
	 	fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
		fread(&m1,sizeof(struct musteri),1,dosya);
	 	if(numara == *m1.hesapNo)
	 	{	 	
		 	kontrol = true;	
			printf("%d %s %s %f %s %s\n",*m1.hesapNo,m1.ad,m1.soyad,m1.bakiye,m1.telefonNo,m1.adres);  
		}		  	 	
	}
	if(kontrol==false)	printf("Kayit bulunamadi");
	fclose(dosya);
	printf("\nMenuye donmek icin herhangi bir tusa basin");
	getch();
}

void bakiyeyenileme()
{
	bool kontrol =false;
 	int boyut,i,num;
 	double ekle;
 	dosya = fopen("hesap.dat","r+b");
 	if(dosya == NULL) if("Dosya acilamadi");
 	printf(" Bakiye ekleyip-cikaracaginiz hesap numarasini giriniz: \n ");
 	scanf("%d",&num);
 	boyut = filelength(fileno(dosya)) / sizeof(struct musteri); //structun boyutu alýndý
 	for(i=0;i<boyut;i++)
 	{
 		fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET); //dosyanýn konumuna gitmek için fseek fonksiyonunu kullandýk
 		fread(&m1,sizeof(struct musteri),1,dosya);
 		if(*m1.hesapNo == num)
		 {
 			kontrol =true;
 			printf(" Eklenilecek-Cikarilacak bakiye: ");
 			scanf("%lf",&ekle);
 			m1.bakiye = m1.bakiye+ekle;
 			fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
 			fwrite(&m1,sizeof(struct musteri),1,dosya); //yeni bakiyeyi güncellemek için tekrardan yazdýrýyoruz
     	}
  	}
 	fclose(dosya);
 	if(kontrol==false)	printf("Kayit bulunamadi");
	printf("\nMenuye donmek icin herhangi bir tusa basin");
	getch();
 }


void hepsiniyazdir()
{
	int i =0;
	bool kontrol =false;
	dosya=fopen("hesap.dat","r");
	boyut=filelength(fileno(dosya))/sizeof(struct musteri);	
 	for(i=0;i<boyut;i++)
	 {
		fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
		fread(&m1,sizeof(struct musteri),1,dosya);
		kontrol =true;
		printf("%d %s %s %f %s %s",*m1.hesapNo,m1.ad,m1.soyad,m1.bakiye,m1.telefonNo,m1.adres);
     }
 if(kontrol==false)	printf("Kayit bulunamadi");
 fclose(dosya);
 printf("\nMenuye donmek icin herhangi bir tusa basin");
 getch();
} 
void isimarama()
{
	char isim[20];
	printf("Aramak istediniz harfi veya heceyi veya kelimeyi giriniz:");
	scanf("%s",isim);
	int i,j;
	bool kontrol =false;
	dosya=fopen("hesap.dat","r");
	boyut=filelength(fileno(dosya))/sizeof(struct musteri);	
 	for(i=0;i<boyut;i++)
	 {	 	
		fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
		fread(&m1,sizeof(struct musteri),1,dosya);
		if(strstr(m1.ad,isim))
		{
			kontrol = true;
			printf("%d %s %s %f %s %s\n",*m1.hesapNo,m1.ad,m1.soyad,m1.bakiye,m1.telefonNo,m1.adres);				
		}	
	 }
	if(kontrol==false)
	{
		printf("Kayit bulunamadi");
	}	
	fclose(dosya);
	printf("\nMenuye donmek icin herhangi bir tusa basin");
	getch();
}
void musteribilgiguncelleme()
{
	bool kontrol =false;
 	int boyut,i,no,karar;
 	char tel[13],adres[99];
 	double ekle;
 	dosya = fopen("hesap.dat","r+b");
 	if(dosya == NULL) if("Dosya acilamadi");
 	printf("Islem yapmak istediginiz hesap numarasini giriniz:");
 	scanf("%d",&no);
 	printf(" 1)Telefon guncellemek\n 2)Adres guncellemek \n 3)Adres ve Telefon guncelleme"); 
	scanf("%d",&karar);	
 	boyut = filelength(fileno(dosya)) / sizeof(struct musteri); //structun boyutu alýndý
 	for(i=0;i<boyut;i++)
 	{
 		fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET); //dosyanýn konumuna gitmek için fseek fonksiyonunu kullandýk
 		fread(&m1,sizeof(struct musteri),1,dosya);
 		if(*m1.hesapNo == no)
		 {
		 	if(karar==1)
		 	{			 
 			kontrol =true;
 			printf("Yeni telefon numarasi:");
 			fflush(stdin);
 			scanf("%s",tel);
 			strcpy(m1.telefonNo,tel);
 			fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
 			fwrite(&m1,sizeof(struct musteri),1,dosya);
 			printf("\nKayit guncellendi");
 			}
 			if(karar==2)
		 	{			 
 			kontrol =true;
 			fflush(stdin);
 			printf("Yeni adres:");
			fgets(adres,99,stdin);	
 			strcpy(m1.adres,adres);
 			fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
 			fwrite(&m1,sizeof(struct musteri),1,dosya);
 			printf("\nKayit guncellendi");
 			}
 			if(karar==3)
 			{
 			kontrol =true;
 			printf("Yeni telefon numarasi:");
 			scanf("%s",tel);
 			fflush(stdin);
 			strcpy(m1.telefonNo,tel);
 			printf("Yeni adres:");
 			fgets(adres,99,stdin);	
 			strcpy(m1.adres,adres);
 			fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
 			fwrite(&m1,sizeof(struct musteri),1,dosya);
 			printf("\nKayit guncellendi");
			}
     	}
  	}
 	fclose(dosya);
 	if(kontrol==false)	printf("Kayit bulunamadi");
	printf("\nMenuye donmek icin herhangi bir tusa basin");
	getch();	
}
void urunkayit()
{
	dosya=fopen( "urun.dat","rb");
	printf("Urun Kodu Giriniz::");
	scanf("%s",u1.kodu);
	printf("Urun Ismi Giriniz:");
	scanf("%s",u1.isim);
	printf("Urun Fiyati Giriniz:");
	scanf("%lf",&u1.fiyat);
	printf("Urun Stok Miktari Giriniz:");
	scanf("%d",&u1.stokmiktari);	
	printf("%s %s %lf %d\n Eklendi",u1.kodu,u1.isim,u1.fiyat,u1.stokmiktari);
	fclose(dosya);
	dosya=fopen( "urun.dat","ab");
	fwrite(&u1,sizeof(struct urun),1,dosya);	
	fclose(dosya);
	printf("\nMenuye donmek icin herhangi bir tusa basin");
	getch();
}
void istenenurun()
{
	int i =0;
	bool kontrol =false;
	dosya=fopen("urun.dat","r");
	boyut=filelength(fileno(dosya))/sizeof(struct urun);
	printf(" 1)Urunu urun koduyla bulma \n 2)Urunu urun ismiyle bulmak \n");
	scanf("%d",&isimaramakontrol);	
	if(isimaramakontrol == 1)
		{	
			printf(" Urun kodunu giriniz: ");
			scanf("%s",c);
		}
	if(isimaramakontrol == 2)
	{	
		printf(" Urun ismini giriniz: ");
		scanf("%s",c);
	}
 	for(i=0;i<boyut;i++)
    {
		fseek(dosya,(i*sizeof(struct urun)),SEEK_SET);
		fread(&u1,sizeof(struct urun),1,dosya);	
		if(isimaramakontrol == 1)
		{			
		 	if(strcmp(c,u1.kodu)==0)
		 	{	
		 		printf("%s %s %lf %d\n",u1.kodu,u1.isim,u1.fiyat,u1.stokmiktari);
				kontrol =true;								
		 	}
			
        }	
    	if(isimaramakontrol == 2)
		{	
			if(strcmp(c,u1.isim)==0)
		 	{
		 		kontrol =true;
				printf("%s %s %lf %d\n",u1.kodu,u1.isim,u1.fiyat,u1.stokmiktari);
	 		}
			
        }		 	
	}
	if(kontrol==false)	printf("Kayit bulunamadi");
	fclose(dosya);
	printf("\n Menuye donmek icin herhangi bir tusa basin");
	getch();
}
void urunbilgiguncelleme()
{
	bool kontrol =false;
 	int boyut,i,no,karar;
 	char kod[20];
 	int stok;
 	double fiyat;
 	double ekle;
 	dosya = fopen("urun.dat","r+b");
 	if(dosya == NULL) if(" Dosya acilamadi");
 	printf(" Islem yapmak istediginiz urun kodunu giriniz:");
 	scanf("%s",kod);
 	printf(" 1)Stok miktari \n 2)Fiyat \n 3)Stok miktari ve fiyati"); 
	scanf("%d",&karar);	
 	boyut = filelength(fileno(dosya)) / sizeof(struct urun); //structun boyutu alýndý
 	for(i=0;i<boyut;i++)
 	{
 		fseek(dosya,(i*sizeof(struct urun)),SEEK_SET); //dosyanýn konumuna gitmek için fseek fonksiyonunu kullandýk
 		fread(&u1,sizeof(struct urun),1,dosya);
 		if(strcmp(kod,u1.kodu)==0)
		 { 
		 	if(karar==1)
		 	{			 
 			kontrol =true;
 			printf(" Yeni stok miktari:");
 			scanf("%d",&stok);
 			u1.stokmiktari = stok;
 			fseek(dosya,(i*sizeof(struct urun)),SEEK_SET);
 			fwrite(&u1,sizeof(struct urun),1,dosya);
 			printf("\n Kayit guncellendi");
 			}
 			if(karar==2)
		 	{			 
 			kontrol =true;
 			printf(" Yeni fiyat:");
 			scanf("%lf",&fiyat);
 			u1.fiyat = fiyat;
 			fseek(dosya,(i*sizeof(struct urun)),SEEK_SET);
 			fwrite(&u1,sizeof(struct urun),1,dosya);
 			printf("\n Kayit guncellendi");
 			}
 			if(karar==3)
 			{
 			kontrol =true;
 			printf(" Yeni stok miktari:");
 			scanf("%d",&stok);
 			u1.stokmiktari = stok;
 			printf(" Yeni fiyat:");
 			scanf("%lf",&fiyat);
 			u1.fiyat = fiyat;
 			fseek(dosya,(i*sizeof(struct urun)),SEEK_SET);
 			fwrite(&u1,sizeof(struct urun),1,dosya);
 			printf("\n Kayit guncellendi");
			}
     	}
  	}
 	fclose(dosya);
 	if(kontrol==false)	printf("Kayit bulunamadi");
	printf("\nMenuye donmek icin herhangi bir tusa basin");
	getch();	
}
void urunsiparis()
{
	bool kontrolbasari = false;
	bool kontrol1 =false;
	bool kontrol2 =false;
 	int boyut,boyut2,i,j;
 	char isim[10];
 	int hesapno[100],miktar;
 	double toplamtutar;
 	yedek = fopen("urun.dat","r+b");
 	dosya = fopen("hesap.dat","r+b");
 	if(dosya == NULL) if(" Dosya acilamadi");
 	if(yedek == NULL) if(" Dosya acilamadi");
 	boyut2=filelength(fileno(yedek))/sizeof(struct urun);
	boyut=filelength(fileno(dosya))/sizeof(struct musteri);	
	if(devamkontrol == true)
	{
		*hesapno = tempmusteri;
	}
	else
	{
		printf(" Musteri numaranizi giriniz:");
		scanf("%d",&hesapno);
	}
	printf(" Urunler:\n");
	for(i=0;i<boyut2;i++)
 	{
 		fseek(yedek,(i*sizeof(struct urun)),SEEK_SET); //dosyanýn konumuna gitmek için fseek fonksiyonunu kullandýk
 		fread(&u1,sizeof(struct urun),1,yedek);
 		printf(" %s %s %lf %d\n",u1.kodu,u1.isim,u1.fiyat,u1.stokmiktari);
	}
	printf(" Almak istediginiz urunun adini giriniz:");
	scanf("%s",isim);
	printf(" Almak istediginiz urunden kac adet almak istediginizi giriniz:");
	scanf("%d",&miktar);
 	for(i=0;i<boyut;i++)
	 {
		fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
		fread(&m1,sizeof(struct musteri),1,dosya);
		if(*m1.hesapNo == *hesapno)
		{
			kontrol1 = true;
			for(j=0;j<boyut2;j++)
 			{
 				fseek(yedek,(j*sizeof(struct urun)),SEEK_SET);
				fread(&u1,sizeof(struct urun),1,yedek);
				if(strcmp(u1.isim,isim)==0)
				{
					kontrol2 =true;
					toplamtutar = (double)miktar * u1.fiyat;
					if(m1.bakiye >= toplamtutar)
					{
						if(u1.stokmiktari-miktar>=0 && u1.stokmiktari>0)
						{
							kontrolbasari = true;
							m1.bakiye-=toplamtutar;						
							u1.stokmiktari -= miktar;						
							fseek(dosya,(i*sizeof(struct musteri)),SEEK_SET);
							fwrite(&m1,sizeof(struct musteri),1,dosya);	 
							fseek(yedek,(j*sizeof(struct urun)),SEEK_SET);
							fwrite(&u1,sizeof(struct urun),1,yedek);
							printf(" 1)Baska urun almak icin\n 2)Siparis sonlandirmak icin");
							scanf("%d",&devam);
							if(devam == 1)
							{
								faturaolusturma(m1,u1,miktar,toplamtutar,devam);
								tempmusteri = *m1.hesapNo;
								devamkontrol = true;
								fclose(dosya);
								fclose(yedek);
								urunsiparis();
							}
							else
							{
								yazdirkontrol = false;
								devamkontrol = false;
								faturaolusturma(m1,u1,miktar,toplamtutar,devam);
							}
						}
						else
						{
							printf("Urun stokta yok\n");				
						}				
					}
					else
					{
						printf(" Bakiye Yetersiz \n");
					}
				}	
			}
		}
		
	 }
	 	fclose(dosya);
		fclose(yedek);
		if(kontrol1 == false)	printf(" Musteri Bulunamadi\n");
		if(kontrol2 == false)	printf(" Urun Bulunamadi\n");	
		if(yazdirkontrol == false)
		{
			if(kontrolbasari == true) 
			{
				printf("Siparis basarili");
				printf("\nMenuye donmek icin herhangi bir tusa basin");
				sipariskontrol = true;
				getch();
				menu();
			}	
		}
		getch();
}
void faturaolusturma(struct musteri m1,struct urun u1,int miktar,double toplamtutar,int devam)
{	
	char dosyaad[40]="";
	char alt[3] = "_";
	char dosyatipi[4] = ".txt";
	strcat(dosyaad,m1.ad);	
	strcat(dosyaad,alt);
	strcat(dosyaad,m1.soyad);
	strcat(dosyaad,dosyatipi);	
	fatura = fopen(dosyaad,"a+");
	if(devam == 1)
	{
		fprintf(fatura,"Alinan Urun:%s \tMiktar:%d \t%Tutar:%lf\n",u1.isim,miktar,toplamtutar);
	}
	else
	{
		fprintf(fatura,"Alinan Urun:%s \tMiktar:%d \t%Tutar:%lf\n",u1.isim,miktar,toplamtutar);
		fprintf(fatura,"Fatura Sahibinin Ismi Soyismi:%s %s\nAdres:%s\nTelefon No:%s\n\n",m1.ad,m1.soyad,m1.adres,m1.telefonNo);	
	}
	fclose(fatura);
	
}
main()
{
	menu();
	return 0;	
}


