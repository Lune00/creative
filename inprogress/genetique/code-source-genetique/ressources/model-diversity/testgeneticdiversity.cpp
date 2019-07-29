#include<iostream>
#include<fstream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<iomanip>

using namespace std;


double mean(const std::vector<double>& values ) {
  if(values.size() == 0 ) return 0. ;
  double mean = 0. ;
  for(int i = 0 ; i != values.size() ; i++ ) {
    mean += values[i] ;
  }
  return mean/(double)(values.size());
}

double var(const std::vector<double>& values ) {
  if(values.size() == 0 ) return 0. ;
  double meanSquared = 0. ;
  for(int i = 0 ; i != values.size() ; i++ ) {
    meanSquared += values[i] * values[i] ;
  }
  meanSquared /= (double)values.size() ;
  double m = mean(values) ;
  return (meanSquared - m * m);
}

double min(const std::vector<double>& values) {

  if (values.size() == 0 ) return 0. ;
  double minVal = values[0] ;

  for(int i = 0 ; i != values.size() ; i++ ) {
    minVal = min(values[i],minVal) ;
  }
  return minVal ;
}

double max(const std::vector<double>& values) {

  if (values.size() == 0 ) return 0. ;
  double maxVal = values[0] ;

  for(int i = 0 ; i != values.size() ; i++ ) {
    maxVal = max(values[i],maxVal) ;
  }
  return maxVal ;
}

void writePdf(const std::vector<double>& values) {

  if(values.size() == 0 ) return ;

  const unsigned int nBins = 50 ; 
  double min = 0. ;
  double max = 9. ;
  double dx = (max - min) / nBins ; 
  std::vector<double> hist( nBins + 1 ) ;

  for(unsigned int i = 0 ; i < values.size() ; i++ ) {
    int p = floor( values[i] / dx ) ;
    hist[ p ] ++ ;
  }

  //Normalise
  for(unsigned int i = 0 ; i < hist.size() ; i++ ) {
    hist[ i ] /= (double)values.size();
  }

  ofstream output ;
  output.open("pdf.txt") ;

  double sum = 0 ;
  for(unsigned int i = 0 ; i < hist.size() ; i++ ) {
    output << ( i - 0.5 ) * dx <<" "<< hist[i] << endl ;
    sum += hist[i] ;
  }

  cout << "Normalisation : " << sum << endl ;
  output.close() ;
}



struct weightedNumber {
  unsigned int number_ ;
  unsigned int w_ ;
  weightedNumber(int number, int w) : number_(number), w_(w) {} ;
};

int sumWeights( const std::vector<weightedNumber>& wn ) {
  int sum = 0 ;
  for(int i= 0; i!= wn.size() ; i++){
    sum += wn[i].w_ ;
  }
  return sum ;
}

int weightedRandomChoice( const std::vector<weightedNumber>& alleles ) {

  //1) Generate a random number between 0 and 1 :
  double r = (random() / (double)RAND_MAX) ;
  r *= sumWeights( alleles ) ;
  for(int i = 0 ; i!= alleles.size() ; i++ ) {
    r -= alleles[i].w_ ;
    if ( r < 0. ) return alleles[i].number_ ;
  }

}


//Generate genes expression with weighted random choice of alleles.
//Really nice resulsts. Allow to control the distribution
void generateSampleWithRandomCombinaisonWeightedAllelesDistribution( ) {

  //// Weighted alleles test :
  std::vector<weightedNumber> alleles ;

  //Pool of initially present alleles with weigh. Modelise the initial population
  alleles.push_back(weightedNumber( 0 , 1)) ;
  alleles.push_back(weightedNumber( 1 , 1)) ;
  alleles.push_back(weightedNumber( 2 , 1)) ;
  alleles.push_back(weightedNumber( 3 , 4)) ;
  alleles.push_back(weightedNumber( 4 , 5)) ;
  alleles.push_back(weightedNumber( 5 , 60)) ;
  alleles.push_back(weightedNumber( 6 , 7)) ;
  alleles.push_back(weightedNumber( 7 , 8)) ;
  alleles.push_back(weightedNumber( 8 , 1)) ;
  alleles.push_back(weightedNumber( 9 , 1)) ;

  int nSamples = 500000 ;
  //We simulation the expression of a Feature with nGenes genes
  int nGenes = 4 ;

  std::vector<double> data ;

  for (int sample = 0 ; sample < nSamples  ; sample++ ) {
    double v = 0. ;
    for( int n = 0 ; n < nGenes ; n++) {
      unsigned int a = weightedRandomChoice( alleles ) ;
      unsigned int b = weightedRandomChoice( alleles ) ;
      double coeff = (random() / (double)RAND_MAX) ;
      v += coeff * a + ( 1 - coeff) * b ;
    }
    //Expression of the feature
    v /= (double)nGenes ;
    data.push_back( v ) ;
  }

  writePdf(data) ;
  cout << std::setprecision(2) <<  "mean : " << mean(data) << " var : " << var(data) << " min : " << min(data) <<" max : " << max(data) << endl ;

  return ;

}


// Generate sample with random combinaisons of alleles : choose n( =ngenes) random pairs among N(nAlleles)
// with n genes expressions for each final value of the feature v
void generateSampleWithRandomCombinaisonsUniformAllelesDistribution() {

  int nalleles = 10 ;
  int nGenes = 3 ;

  int nSamples = 500000 ;
  std::vector<double> data ;

  for (int sample = 0 ; sample < nSamples  ; sample++ ) {
    double v = 0. ;
    for( int n = 0 ; n < nGenes ; n++) {
      unsigned int a = rand() % nalleles ;
      unsigned int b = rand() % nalleles ;
      double coeff = (random() / (double)RAND_MAX) ;
      //double coeff = 0.3 ;
      v += coeff * a + ( 1 - coeff) * b ;
    }
    v /= (double)nGenes ;
    data.push_back( v ) ;
  }

  //Statistics : mean , std , pdf , min , max
  writePdf(data) ;
  cout << std::setprecision(2) <<  "mean : " << mean(data) << " var : " << var(data) << " min : " << min(data) <<" max : " << max(data) << endl ;
  return ;
}


int main(){

  generateSampleWithRandomCombinaisonWeightedAllelesDistribution() ;
  return 0 ;

}
