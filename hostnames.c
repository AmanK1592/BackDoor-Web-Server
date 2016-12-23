#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{	

//---------------------------------------------------------------------------------For reading /etc/hosts file---------------------------------------------------------------------------------------
	FILE *p;												//file pointer for /etc/hosts
	
	char str[1000];											//Str to read the /etc/hosts file line by line				
	
	char ip[1000];											//char arrays to store the ip address, hostname and the alias
	char host[1000];
	char alias[1000];


	//p=fopen("/etc/hosts","r");
	p=fopen("/etc/hosts","r");								//Opening the file /etc/hosts

	if(p == NULL)											//Checking if it is a valid file
	{
		//printf("Cannot open the target file\n");
			
	}

	else
	{	

		while(fgets(str,1000,p)!=NULL)							//Reading the file into str line by line	
		{
			sscanf(str,"\t %s \t %s \t %s",ip,host,alias);		//Creating a new file cancelling out the whitespaces and storing the elements in char arrays
			
			if(str[0] != '#' && str[0] != '\n' && ip[0] != '#')	//Checking for conditions
			{
				//if(host[0]!='i' && host[1]!='p'&& host[2]!='6')	//Displaying the hostnames in /etc/hosts
				//{	
				if(isdigit(host[0]) == 0)
				{
					puts(host);	
				}
				
				if(isdigit(alias[0]) == 0)
				{
					if(alias[0] != '\0')
				{
						puts(alias);									

				}

				}	
				

					
				//}
			}				
				
		}
	
			
	}
	//fclose(p);													//Closing the file 

//--------------------------------------------------------------------------------------------For reading /etc/ssh/ssh_config--------------------------------------------------------------------------------
	FILE *a;																		//Declaring a file pointer

	char s[1000];
	char h[1000];
	char t[1000];

	a=fopen("/etc/ssh/ssh_config","r");												//Opening the file

	if(a == NULL)
	{
		//printf("Cannot open the target file\n");
		
	}
	else
	{
		while(fgets(s,1000,a)!=NULL)												//Checking for conditions
		{
			sscanf(s,"\t %s \t %s",t,h);
			if(s[0] != '#' && s[0] != '\n')
			{
				if((t[0] == 'H' && t[1] == 'o' && t[3] == 't') || (t[4] == 'N'))
				{
					if(h[0] != '*')
					{
						if(isdigit(h[0]) == 0)
						puts(h);													//Displaying the hostnames

					}
					

				}


			}

		}
		

	}





	
//--------------------------------------------------------------------------------------------- extracting hosts from the .ssh/config file-------------------------------------------------------------------	
	
	FILE *pwd;							//file pointer for opening the etc/passwd file
	FILE *usr;							//file pointer for opening the path obtained for the hosts from the passwd file

	char str1[1000];						//str1 to read the passwd file line by line
	char str2[1000];						//str2 to read the sub.ssh/config files in the independent users folder
	char hostname[1000];					//for obtaining the hostnames from the passwd file
	
	char title[1000];					//arrays for storing the hostnames from the .ssh/config
	char hostname1[1000];					
	
	
	pwd=fopen("/etc/passwd","r");					//Opening the passwd file

	if(pwd == NULL)									//Checking if it is valid or not
	{
		//printf("Cannot open the target file\n");
			
	}

	else
	{	
		while(fgets(str1,1000,pwd)!=NULL)			//Read the file into str1 line by line
		{
			sscanf(str1,"%[^:]%s:",hostname);	//Creating a new file and delimiting elements using :

			if(str1[0] != '#' && str1[0] != '\n') 	//Checking for conditions 
			{			
				
				//puts(hostname);						//Displaying the host names in the passwd file
				
				char fullpath[100]="/home/";		//Creating the fullpath to open the sub .ssh/config files from
				strcat(hostname,"/");
				strcat(hostname,".ssh/config");
				strcat(fullpath,hostname);
				//puts(fullpath);


				usr = fopen(fullpath,"r");			//using a file pointer to open a file specified by the fullpath
				
				if(usr == NULL)						//Checking if the config file exists
				{

				}
				else
				{
			
					while(fgets(str2,1000,usr)!=NULL)	//Reading the file into str2 line by line
					{
						sscanf(str2,"\t %s \t %s",title,hostname1);	//Extracting the title"HostName" and the host name

						if(str2[0] != '#' && str2[0] != '\n')		//Checking for conditions
						{
							if((title[0] == 'H' && title[1] == 'o' && title[3] == 't') || (title[4] == 'N'))
							{
								if(hostname1[0] != '*')
								{
									if(isdigit(hostname1[0]) == 0)
									//if(hostname1[0] != '.' || hostname1[7] != '.')
									//if(hostname1[3] != '.' && hostname1[7] != '.')
									puts(hostname1);				//Displaying the hostnames in the .ssh/config file

								}
													
							}

						}

					}
						
					
				}

				fullpath[0]=0;										//Clearing the fullpath variable for every iteration


			}
		}

		//fclose(usr);												//Closing the file	
		

	}
	
	
	//fclose(pwd);													//Closing the file

//----------------------------------------------------------------------------------.ssh/authorized_keys---------------------------------------------------------------------------------------------------
	FILE *fptr;										//file pointer for opening the path obtained for the hosts from the passwd file
	FILE *pwd1;										//file pointer for opening the etc/passwd file

	char str3[1000];								//char arrays for storing the values
	char str4[1000];
	char hostname2[500];
	char key[1000];
	char hostname3[500];
	char key_format[100];
	char final[1000];

	pwd1=fopen("/etc/passwd","r");					//Opening the passwd file
	if(pwd1==NULL)									//Checking if it is valid or not
	{
		//printf("Cannot open the target file\n");
		
	}
	else
	{	
		while(fgets(str3,1000,pwd1)!=NULL)			//Read the file into str3 line by line
		{
			sscanf(str3,"%[^:]%s:",hostname2);	//Creating a new file and delimiting elements using :

			if(str3[0] != '#' || str3[0] != '\n') 	//Checking for conditions 
			{			
				
				//puts(hostname);						//Displaying the host names in the passwd file
				
				char fp[100]="/home/";		//Creating the fullpath to open the sub .ssh/config files from
				strcat(hostname2,"/");
				strcat(hostname2,".ssh/id_rsa.pub");
				strcat(fp,hostname2);
				//puts(fp);

				fptr = fopen(fp,"r");

				if(fptr!= NULL)						//Checking if the config file exists
				{
				
					while(fgets(str4,1000,fptr)!=NULL)	//Reading the file into str4 line by line
					{	
						sscanf(str4,"\t %s \t %s \t %s",key_format,key,hostname3);	//Extracting the hostnames
						sscanf(hostname3,"%[^@]%s@",final);

						if(str4[0] != '#' && str4[0] != '\n')		//Checking for conditions
						{
							if(isdigit(final[0]) == 0)
							{
								puts(final);						//Displaying the hostnames in the authorized_keys
							}//puts(key_format);
							//puts(key);

						}
					}
				}

				fp[0] = 0;

				
			}

		}
		
		//printf("Before");
		//fclose(fptr);
		
		
		
	}

	
	//fclose(pwd1);


//-----------------------------------------------------------------------known_hosts-----------------------------------------------------------------------------------------------------------------------
	FILE *fptr1;									//file pointer for opening the path obtained for the hosts from the passwd file
	FILE *pwd2;										//file pointer for opening the etc/passwd file
	
	char str5[1000];								
	char str6[1000];
	char hostnames[1000];
	char hostname4[1000];
	char level[1000];
	char key1[1000];
	char host1[1000];
	char ip1[1000];

	
	pwd2=fopen("/etc/passwd","r");					//Opening the passwd file

	if(pwd2 == NULL)									//Checking if it is valid or not
	{
		//printf("Cannot open the target file\n");
		
	}

	else
	{	
		while(fgets(str5,1000,pwd2)!=NULL)			//Read the file into str5 line by line
		{
			sscanf(str5,"%[^:]%s:",hostnames);	//Creating a new file and delimiting elements using :

			if(str5[0] != '#' && str5[0] != '\n') 	//Checking for conditions 
			{			
				
				//puts(hostnames);						//Displaying the host names in the passwd file
				
				char fullpath[100]="/home/";		//Creating the fullpath to open the sub .ssh/known_hosts file
				strcat(hostnames,"/");
				strcat(hostnames,".ssh/known_hosts");
				strcat(fullpath,hostnames);
				//puts(fullpath);

				fptr1 = fopen(fullpath,"r");			//using a file pointer to open a file specified by the fullpath
				
				if(fptr1 == NULL)						//Checking if the config file exists
				{

				}
				else
				{
					while(fgets(str6,1000,fptr1)!=NULL)					//Checking for conditions
					{
						sscanf(str6,"\t %s \t %s \t %s",hostname4,level,key1);
						if(hostname4[0] != '[' && (isdigit(hostname4[0]) == 0))
						{	
								sscanf(hostname4,"%[^,]%s \t",host1,ip1);
								if(isdigit(host1[0]) == 0)
								{
									puts(host1);						//Displaying the hostnames
								}
								
								//puts(hostname4);	
						}
					}
				}
				fullpath[0]=0;
			}
		}
	}




	/*fptr1=fopen("known_hosts","r");					//Opening the passwd file
	if(fptr1==NULL)									//Checking if it is valid or not
	{
		printf("Cannot open the target file\n");
		return 1;	
	}*/

//-----------------------------------------------------------------------------------------------------------For /etc/ssh/ssh_known_hosts------------------------------------------------------------------------------------------------
	FILE *b;													//Declaring a file pointer

	char s2[1000];												//Char arrays
	char h2[1000];
	char lvl[1000];
	char k[1000];
	char h3[1000];
	char ip2[1000];

	b=fopen("/etc/ssh/ssh_known_hosts","r");					//Opening the file
	if(b == NULL)
	{
		//printf("Cannot open the target file\n");
		
	}

	else
	{
		while(fgets(s2,1000,b)!=NULL)							//Checking for conditions
		{
		sscanf(s2,"\t %s \t %s \t %s",h2,lvl,k);
			if(h2[0] != '[' && (isdigit(h2[0])==0))
			{
				sscanf(h2,"%[^,]%s \t",h3,ip2);
				if(isdigit(h3[0]) == 0)
				{
					puts(h3);								//Displaying the hostnames
				}
				
			}

		}
	}

//---------------------------------------------------------------------------------------------------------------authorized_keys-------------------------------------------------------------------------------------------------------------
	FILE *fptr2;								//file pointer for opening the path obtained for the hosts from the passwd file
	FILE *pwd3;									//file pointer for opening the etc/passwd file

	char str7[1000];
	char str8[1000];
	char sec[1000];
	char key2[1000];
	char user1[1000];
	char username[1000];
	char name[1000];

	pwd3=fopen("/etc/passwd","r");					//Opening the passwd file

	if(pwd3 == NULL)									//Checking if it is valid or not
	{
		//printf("Cannot open the target file\n");
			
	}
	else
	{
		while(fgets(str7,1000,pwd3)!=NULL)			//Read the file into str7 line by line
		{
			sscanf(str7,"%[^:]%s:",hostnames);	//Creating a new file and delimiting elements using :

			if(str7[0] != '#' && str7[0] != '\n') 	//Checking for conditions 
			{			
				
				//puts(hostnames);						//Displaying the host names in the passwd file
				
				char fullpath[100]="/home/";		//Creating the fullpath to open the sub .ssh/authorized_keys from
				strcat(hostnames,"/");
				strcat(hostnames,".ssh/authorized_keys");
				strcat(fullpath,hostnames);
				//puts(fullpath);
				fptr2 = fopen(fullpath,"r");			//using a file pointer to open a file specified by the fullpath
				
				if(fptr2 == NULL)						//Checking if the config file exists
				{

				}
				else
				{
					while(fgets(str8,1000,fptr2)!=NULL)
					{
						sscanf(str8,"\t %s \t %s \t %s", sec,key2,user1);
						if(user1[0] != '/')
						{
							sscanf(user1,"%[^@]@%s",name,username);
							if(isdigit(username[0]) == 0)
							{

								puts(username);				//Displaying the hostnames

							}
							
						}
			
					}

				}
				fullpath[0]=0;
			}
		}
	}
		


	return 0;
}