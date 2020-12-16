#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <math.h>
#include "gnuplot.h"

using namespace std;

double time=0.1; //sec, cas jednotlivych mereni arduina

void graf_gnu()
{
	gnuplot p;
		
	p("set terminal wxt 0"); // wxt(linux?), windows, qt(mac) a nejake dalsi jsou druhy terminalu
	p("set title \"Teplota\"");
	p("set xlabel \"Cas\"");
	p("set ylabel \"Teplota\"");	
	p("plot  \'_temperature.txt\' w l lt rgb \"yellow\" title \"Teplota ARD\"");

	p("set terminal wxt 1");	
	p("set title \"Zrychlení\"");
	p("set xlabel \"Cas\"");
	p("set ylabel \"Zrychleni\"");	
	p("plot  \'_acc.txt\' w filledcurves x1 lt rgb \"red\" title \"Zrychleni ARD\", \'_acc.txt\' w p title \"Body ARD\""); 
		
	
	p("set terminal wxt 2");
	p("set title \"Rychlost\"");
	p("set xlabel \"Cas\"");
	p("set ylabel \"Rychlost\"");
	p("plot  \'_vel.txt\' w filledcurves x1 lt rgb \"blue\" title \"Rychlost ARD\", \'_vel.txt\' w p title \"Body ARD\""); 
	
	
	
	p("set terminal wxt 3"); // aby se otevrelo dalsi okno je potreba dalsi terminal, staci tam pridat cislo
	p("set title \"Trajektorie\"");
	p("set xlabel \"x\"");
	p("set ylabel \"y\"");
	p("plot  \'_loc.txt\' w l title \"Trajektorie ARD\", \'_loc.txt\' w p title \"Body ARD\"");
	
	p("set terminal wxt 4"); 
	p("set xlabel \"x\"");
	p("set ylabel \"z\"");
	p("plot  \'_loc.txt\' u 2:3 w l title \"Trajektorie ARD\", \'_loc.txt\' u 2:3 w p title \"Body ARD\""); // u 2:3, je using columns 2 a 3, automaticky to bere od jednicky

	p("set terminal wxt 5");
	p("set xlabel \"x\"");
	p("set ylabel \"y\"");
	p("set zlabel \"z\"");
	p("set title \"Trajektorie\"");
	p("splot  \'_loc.txt\' w l title \"Trajektorie ARD\", \'_loc.txt\' w p title \"Body ARD\""); // splot je 3D graf
}

void acceleration(	const vector<double> &datax, const vector<double> &datay, const vector<double> &dataz, 
				          vector<double> &accx, vector<double> &accy, vector<double> &accz, vector<double> &acc)
{
	/*double tempx,tempy,tempz,temp;
	for (int i = 0; i<datax.size()-1 ; ++i)
	{
		/*if(i==0)
		{
			tempx = ((datax[i]-datax[0]));
			accx.push_back(tempx);
		
			tempy = ((datay[i]-datay[0]));
			accy.push_back(tempy);
		
			tempz =((dataz[i]-dataz[0]));
			accz.push_back(tempz);	
		}
		else 
		{
			if(datax[i]>datax[i-1])
			{
				tempx = ((datax[i]-datax[i-1]));
				accx.push_back(tempx);
			}
			else
			{
				tempx = -((datax[i-1]-datax[i]));
				accx.push_back(tempx);
			}
			if(datay[i]>datay[i-1])
			{
				tempy = ((datay[i]-datay[i-1]));
				accy.push_back(tempy);
			}
			else
			{
				tempy = -((datay[i-1]-datay[i]));
				accy.push_back(tempy);
			}
		}

		tempz = (dataz[i]-tempz);
		accz.push_back(tempz);
		if(i==0)
		{
			tempx = ((datax[i]-datax[0]));
			accx.push_back(tempx);
		
			tempy = ((datay[i]-datay[0]));
			accy.push_back(tempy);
		
			tempz = ((dataz[i]-dataz[0]));
			accz.push_back(tempz);			
		}
		else
		{
			if(datax[i]-datax[i-1]<0.1)
			{
			tempx =0;
			accx.push_back(tempx);
			}
			else
			{
			tempx =((datax[i]-datax[0]));
			accx.push_back(tempx);
			}
			
			if(datay[i]-datay[i-1]<0.1)
			{
			tempy = 0;
			accy.push_back(tempy);
			}
			else
			{
			tempy = ((datay[i]-datay[0]));
			accy.push_back(tempy);
			}
			
			if(dataz[i]-dataz[i-1]<0.2)
			{
			tempz = 0;
			accz.push_back(tempz);
			}
			else
			{
			tempz = (dataz[i]-dataz[0]);
			accz.push_back(tempz);
			}
		
					
		}
		temp=sqrt(tempx*tempx + tempy*tempy + tempz*tempz);
		acc.push_back(temp);
	}*/	
	double tempx,tempy,tempz,temp;
	for (int i = 0; i<datax.size()-1 ; ++i)
		{
			tempx = datax[i]-datax[0];
			accx.push_back(tempx);
			
			tempy = datay[i]-datay[0];
			accy.push_back(tempy);
			
			tempz = dataz[i]-dataz[0];
			accz.push_back(tempz);
			
			temp=sqrt(tempx*tempx + tempy*tempy + tempz*tempz);
			acc.push_back(temp);
		}
	
}

void velocity(	const vector<double> &accx, const vector<double> &accy, const vector<double> &accz, 
				      vector<double> &velx, vector<double> &vely, vector<double> &velz, vector<double> &vel)
{
	double tempx,tempy,tempz,temp;
	for (int i = 0; i<accx.size()-1 ; ++i)
		{
		if(i==0)
			tempx=0;
		tempx = accx[i]*time+tempx;
		velx.push_back(tempx);
		if(i==0)
			tempy=0;
		tempy = accy[i]*time+tempy;
		vely.push_back(tempy);
		
		if(i==0)
			tempz=0;
		tempz = accz[i]*time+tempz;
		velz.push_back(tempz);
		
		temp=sqrt(tempx*tempx + tempy*tempy + tempz*tempz);
		vel.push_back(temp);
		}
}

void location(	const vector<double> &accx, const vector<double> &accy, const vector<double> &accz, 
				const vector<double> &velx, const vector<double> &vely, const vector<double> &velz,
					  vector<double> &locx, vector<double> &locy, vector<double> &locz)
{
	double tempx,tempy,tempz,temp;
	for (int i = 0; i<velx.size() ; ++i)
		{
		if(i==0)
			tempx=0;
		tempx = velx[i]*time+tempx;
		locx.push_back(tempx);
		
		if(i==0)
			tempy=0;
		tempy = vely[i]*time+tempy;
		locy.push_back(tempy);
		
		if(i==0)
			tempz=0;
		tempz = velz[i]*time+tempz;
		locz.push_back(tempz);
	}
}

void zapis (const vector<double> &acc, const vector<double> &vel, 
			const vector<double> &accx, const vector<double> &accy, const vector<double> &accz,
			const vector<double> &velx, const vector<double> &vely, const vector<double> &velz,
			const vector<double> &locx, const vector<double> &locy, const vector<double> &locz, 
			const vector<double> &temperature)
{
	ofstream file_acc;
	file_acc.open("_acc.txt");
	ofstream file_acc2;
	file_acc2.open("_acc2.txt");
	ofstream file_vel;
	file_vel.open("_vel.txt");
	ofstream file_vel2;
	file_vel2.open("_vel2.txt");
	ofstream file_loc;
	file_loc.open("_loc.txt");
	ofstream file_tem;
	file_tem.open("_temperature.txt");
	
	for (int i =0 ; i<acc.size()-1 ; ++i)
	{
		file_acc  << time*(i) <<  "	" << acc[i]  << endl; //
		file_acc2 << accx[i] << "	" <<accy[i] << "	" << accz[i] << endl;
		file_vel << time*(i) <<  "	" << vel[i] << endl; //
		file_vel2 << velx[i] << "	" <<vely[i] << "	" << velz[i] << endl;
		file_loc << locx[i] << "	" <<locy[i] << "	" << locz[i] << endl;
		file_tem << time*(i) <<  "	" << temperature[i] << endl;
	}
	
	file_acc.close();
	file_vel.close();
	file_loc.close();
	file_tem.close();
	file_acc2.close();
	file_vel2.close();
}

bool nacteni(vector<double> &datax, vector<double> &datay, vector<double> &dataz, vector<double> &temperature)
{
	double temp;
	ifstream file;
		
	file.open("data_upraveno.txt");
	if(file.fail())
	{
		cout << "Nepodarilo se nacist soubor" <<endl;
		return 1;
	}
	
	while(!file.eof())
	{
		if(file.eof())
			break;
		temp = 0;
		file >> temp;
		datax.push_back(temp);
		file >> temp;
		datay.push_back(temp);
		file >> temp;
		dataz.push_back(temp);
		file >> temp;
		//temp=0;
		temperature.push_back(temp);		
	}
	
	file.close();
	return 0;
}

int main()
{
	vector<double> datax, datay, dataz, temperature;
		//nacteni dat
	bool ret=nacteni(datax,datay,dataz,temperature);
	if(ret==1)
		return 1; 
	//zpracovani dat	
	vector<double> locx, locy, locz;
	vector<double> accx, accy, accz, acc;
	vector<double> velx, vely, velz, vel;
	acceleration(datax,datay,dataz,accx,accy,accz,acc);
	velocity(accx,accy,accz,velx,vely,velz,vel);
	location(accx,accy,accz,velx,vely,velz,locx,locy,locz);	
	//zapis dat do souboru
	zapis(acc,vel,accx,accy,accz,velx,vely,velz,locx,locy,locz,temperature);
	//vypis grafu
	graf_gnu();
	return 0;
}
