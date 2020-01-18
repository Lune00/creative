package supermarketQueue;

public class Solution {

	public static int solveSuperMarketQueue(int[] customers, int n) {

		//If more tills thant customers number of tills = number of customers
		if (n > customers.length) {
			n = customers.length;
		}

		int[] tills = new int[n];

		int time = 0;

		//Initialise tills : tills is an array of pointer to customer, their value is the index of current customer
		for (int i = 0; i != n; i++) {
			tills[i] = i;
		}

		while (sum(customers) != 0) {

			//Iterate through tills
			for (int i = 0; i != n; i++) {
				
				
				//If tills point not longer to a customer ignore it
				if(tills[i] == - 1) {
					continue;
				}	
				
				//If customer[ tills[i] ] has finished, tills[i] store the index of the next customer
				if(customers[ tills[i] ] == 0) {
					tills[i] = nextFreeCustomerIndex(customers, tills);
				}
				
				//If tills point to a customer, decrement customer time by 1
				if(tills[i] != - 1) {
					customers[ tills[i] ] -= 1 ;
				}				
				
			}
			
			
			affiche(customers,time);
			
			time += 1;

		};

		return time;
	}
	
	
	
	//Return the next free customer index (ie customers[index] != 0 and tills[] != index ) , -1 if none
	private static int nextFreeCustomerIndex(int[] customers, int [] tills) {
		for(int i = 0; i != customers.length; i++ ) {
			if(customers[i] != 0) {
				if(!nextCustomerAlreadyPointedByATill(i, tills)) {
					return i;
				}
			}
		}
		return - 1;
	}
	
	private static boolean nextCustomerAlreadyPointedByATill(int customerIndex, int[] tills) {
		
		for(int i = 0 ; i != tills.length; i++) {
			if( tills[i] == customerIndex ) {
				return true;
			}
		}
		return false;
	}

	
	private static int sum(int[] a) {
		int sum = 0;
		for (int i = 0; i != a.length; i++) {
			sum += a[i];
		}
		return sum;
	}
	
	private static void affiche(int[] a, int time) {
		System.out.print("time="+time+" ");
		for (int i = 0; i != a.length; i++) {
			System.out.print(a[i]+" ");
		}
		System.out.println();
	}

}
