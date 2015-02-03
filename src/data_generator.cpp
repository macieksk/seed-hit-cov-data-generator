#include <iostream>
#include <cassert>
#include <cstring>
#include <random>

using namespace std;

#define HELP_TEXT "USAGE: data_generator read_length min_id_rate seed iterations\n"

#define MATCH 1
#define MISMATCH -4

int main(int argc, char* argv[])
{
	if(argc!=5){
		cout << HELP_TEXT << endl;
		return 1;
	}

	int rlen = atoi(argv[1]);
	float max_err_rate = 1-atof(argv[2]);
	char* seed = argv[3];
	int n=atoi(argv[4]);
	int seedlength=(int)strlen(seed);
	
	assert(seedlength <= rlen);
	assert(n>0);
	for (int i=0;i<seedlength;i++){
		assert(seed[i]=='#' || seed[i]=='-');
	}

	random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	cout << endl;
	cout << "########################" << endl;
	cout << "# read_length:          " << rlen << endl;
	cout << "# seed:                 " << seed << endl;
	cout << "# number of iterations: " << n << endl;
	cout << "# minimal id rate:      " << 1-max_err_rate << endl;
	cout << "" << endl;
	cout << "Ham\tSco\tHits\tCov\tNoover" << endl;

	char *similarity = new char[rlen];
	/* Part 1: compute the expectations and variances */
	for (int i=1;i<n+1;i++){
		//if(i % (n / 10)  ==1 && i!=1){
		//	cerr << "Iteration " << i << endl;
		//}

	  int hamming=0;
	  int score=0;
	  int Overhits=0;
	  int Nonoverhits=0;
	  int Grouphits=0;
	  /* generate random error rate between 0 and max_err_rate */
	  auto errrate=dis(gen);
	  errrate *= max_err_rate;
	  /* generate random similarity with errrate  */
	  for(int j=0;j<rlen;j++){
	    auto rand=dis(gen);
	    if (rand<=errrate){
	      /* mismatch */
	      similarity[j]=0;
	      hamming++;
	    }
	    else{
	      /* match */
	      similarity[j]=1;
	    }
	  }
	  /* compute score */
	  score = (rlen-hamming) * MATCH + hamming * (MISMATCH);

	  /* compute number of hits in similarity WITH OVERLAP */
	  for(int j=0;j<rlen-seedlength+1;j++) {
	    bool ok=true;
	    for(int t=0;t<seedlength;t++){
	      if (seed[t]=='#' && similarity[j+t]==0){
		/* it does not detect at this position */
		ok=false;
		break;
	      }
	    }
	    if(ok){
	      Overhits++;
	    }
	  }
	  
	  /* compute number of hits in similarity WITHOUT OVERLAP */
	  int j=0;
	  while (j<rlen-seedlength+1) {
	    bool ok=true;
	    for(int t=0;t<seedlength;t++){
	      if (seed[t]=='#' && similarity[j+t]==0){
		/* it does not detect at this position */
		ok=false;
		break;
	      }
	    }
	    if(ok){
	      Nonoverhits++;
	      j+=seedlength;
	    }
	    else {j++;}
	  }

	  /* compute nb of matches covered by all hits in similarity */
	  // int end_of_last_match=-1;
	  string covered(rlen, 0);
	  for(int j=0;j<rlen-seedlength+1;j++) {
	    bool ok=true;
	    for(int t=0;t<seedlength;t++){
	      if (seed[t]=='#' && similarity[j+t]==0){
		/* it does not detect at this position */
		ok=false;
		break;
	      }
	    }
	    if(ok){
	      /* sets corresponding bits in covered to 1 */
	      for(int t=0;t<seedlength;t++){
		if (seed[t]=='#') covered[j+t]=1;
	      }
	    }
	  }
	  /* count number of 1s in covered */
	  for (int j=0;j<rlen;j++) {
	    if (covered[j]==1) Grouphits++;
	  }

	  /* Print results */
	  cout << hamming << "\t" << score << "\t" << Overhits << "\t" << Grouphits << "\t" << Nonoverhits << endl;

	}

	return 0;
}
