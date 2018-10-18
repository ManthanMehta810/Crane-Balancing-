#include<iostream>
#include<cmath>

using namespace std;
int x[2000],y[2000];
class cranebalance
{
	int n,i,minX,maxX;
	double area,cx,cy,cross;
    bool assigned;
	double w,loww,highw;
	
	public:
		cranebalance()
		{
			minX = 0;
			maxX = 0;
			area = 0;
			cx = 0;
			cy = 0;
			assigned = false;
		}
		void input();
        void calculation();
        void results();
};

void cranebalance::input()
{
    cout<<"\nEnter number of nodes: ";
    cin>>n;
}

void cranebalance::calculation()
{
	for(i=0;i<n+1;i++)
	{
		if(i<n)
		{
			cin>>x[i];
			cin>>y[i];
		}
		else
		{
			x[i]=x[0];
			y[i]=y[0];
		}

		if(y[i] == 0)
		{
			if(!assigned)
			{
				minX = x[i];
				maxX = x[i];
				assigned = true;
			}
			else if(x[i] < minX)
			{
				minX = x[i];
			}
			else if(x[i] > maxX)
			{
				maxX = x[i];
			}
		}
 // Centre of Mass and area
		if( i > 0)
		{
			cross = x[i-1]*y[i] - x[i]*y[i-1];
			area =area+cross;
			cx = cx+(x[i-1]+x[i])*cross;
			cy = cy+(y[i-1]+y[i])*cross;

		}
	}

	area =area/2;
	cx = cx/(6*area);
	cy = cy/(6*area);
	area = abs(area); 

	cout<<"\n"<<area;
	cout<<"\n"<<cx;
	cout<<"\n"<<cy;
	cout<<"\n"<<minX<<"\n"<<maxX;
 
}

void cranebalance::results()
{
  //unstable cases
	if(cx < minX && x[0] <= minX)
	{
		cout<<"\nThe crane is unstable\n\n";
	}
	else if(cx > maxX && x[0] >= maxX)
	{
		cout<<"\nThe crane is unstable\n\n";
	}
  //Infinity Load
	else if(x[0] >= minX && x[0] <= maxX && cx >= minX && cx <= maxX)
	{
		cout<<"\nThe crane takes load = 0..inf\n\n";
	}
	else
	{
    //Centroid x is within the base
		if(cx >= minX && cx <= maxX)
		{
      //Load Hanging off the right
			if(x[0] > maxX)
			{
				w = (long double)((maxX - cx)/(x[0] - maxX)*area + 1 );

				if(w>0)
				{

					cout<<"\nThe crane takes load = 0.."<<(int)w<<"\n\n";
				}
				else
				{
					cout<<"\nThe crane is unstable";
				}
			}
      //Hanging point not off the right
			else
			{
				w = (long double)( (cx - minX)/(minX - x[0])*area + 1 );

				if(w > 0)
				{
					cout<<"\nThe crane takes load = 0.."<<(int)w<<"\n\n";
				}
				else
				{
					cout<<"\nThe crane is unstable\n\n";
				}
			}
		}

    //Centroid x is the left
		else if(cx < minX)
		{
      //Hanging point off the right
			if(x[0] > maxX)
			{
				loww = (long double)((minX - cx)/(x[0]-minX)*area );
				highw = (long double)( (maxX - cx)/(x[0] - maxX)*area + 1 );
				cout<<"\nThe crane takes load = "<<(int)loww<<" .. "<<(int)highw<<"\n\n";
			}	
      //Hanging point not off the right
			else
			{
				w = (long double)((minX - cx)/(x[0]-minX)*area );
				cout<<"\nThe crane takes load = "<<(int)w<<" .. inf\n\n";
			}
		}
    //centroid x is to the right
		else
		{
			if(x[0] < minX)
			{
				loww = (long double)((cx - maxX)/(maxX-x[0])*area );
				highw = (long double)((cx - minX)/(minX - x[0])*area  + 1 );
				cout<<"\nThe crane takes load = "<<(int)loww<<" .. "<<(int)highw<<"\n\n";
			}
      //Not to the left
			else
			{
				w = (long double)((cx - maxX)/(maxX-x[0])*area );
				cout<<"\nThe crane takes load = "<<(int)w<<" .. inf\n\n";
			}
		}
	}
}

int main()
{
	cranebalance c;
	cout<<"\n\t\t***** CRANE BALANCING *****";
	c.input();
	c.calculation();
	c.results();
	return 0;
}