#include <iostream>
#include <vector>
#include <algorithm> // Needed for std::sort
#include <cmath>     // For Math stuff
#include <iomanip>   // For std::setprecision

using namespace std;

int main() {
    cout << "Hey, I'll do some statistics for you. \nHow many data points do you have? ";
    int n;
	// Initialize variables for lmed, fm, and gm
	float lmed = 0; // Minimum value of the category with gi >= n/2
	int fm = 0;   // Frequency of the category with gi >= n/2
	float gm = 0; // Highest gi < n/2
	// Initialize cumulative frequency (cf) and cumulative relative frequency (crf)
	int cf = 0;
	float crf = 0;
    cin >> n;
    
    int n2 = n/2;
        
    vector<float> data(n); // Using a vector to store 'n' data points.

    cout << "Now give me the whole data:\n(separate each number with a space)\n ";

    // Reading 'n' data points into the vector
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    // Sorting the data - std::sort uses a default ascending order
    sort(data.begin(), data.end());

    // Print the sorted data
    cout << "\nSorted data:\n";
    for (int i = 0; i < n; ++i) {
        cout << fixed << setprecision(2) << data[i] << " ";
        if ((i + 1) % 10 == 0) {
            cout << endl; // Start a new line every 10 data points
        }
    }
    cout << endl;

    // Max and Min Data
    float max_value = data.back();
    float min_value = data.front();

    // Calculate the number of groups (categories)
    float k = 1 + 3.322 * log10(n);
    

    // Calculate the width of each group
    float w = (max_value - min_value) / k;
   	float r = max_value - min_value;

    // Initialize variables for the table
    cout << "\nCategories\tMin\tMax\t xi\t fi\t ri\t gi\t si\t fixi\t\t fixi^2" << endl;

    // Initialize ri and gi for the first category
    float ri_prev = 0;
    float gi_prev = 0;
  
  
  // Define arrays for fi and xi
  vector<int> fi_values(n); // Frequency values
  vector<float> xi_values(n); // Midpoint values
  vector<float> gi_values(n); // relative frequent value 
    
    // Calculate and display the table entries
    for (int i = 0; i < k; ++i) {
        float category_start = min_value + i * w;
        float category_end = category_start + w;
        float xi = (category_start + category_end) / 2;

        // Calculate the frequency (number of data points in the group)
        int fi = 0;
        for (int j = 0; j < n; ++j) {
            if (data[j] >= category_start && data[j] < category_end) {
                ++fi;
            }
        }
         // Update arrays for fi and xi
        fi_values[i] = fi;
        xi_values[i] = xi;

        // Calculate gi
        float gi = fi + gi_prev;
        gi_prev = gi;
          if (gi < n2 && gi > gm) {
        gm = gi;
    }

        // Calculate ri (relative frequency)
        float ri = static_cast<float>(fi) / n;

        // Calculate si (summarizing gi with gi of the category before)
        float si = ri + ri_prev;
        ri_prev = si;

        float fixi = fi * xi;
        float fixi_squared = fixi * xi;

        cout << i + 1 << "\t\t" << category_start << "\t" << category_end << "\t" << xi << "\t " << fi << "\t " << ri << "\t " << gi << "\t " << si << "\t " << fixi << "\t\t " << fixi_squared << endl;
    }
    
    
    
   cout << "Number of groups (categories): " << k << endl;
   cout << "Width of each group: " << w << endl;
    
  // Calculate the mode
  int max_freq = 0;
  vector<float> modes;
  for (int i = 0; i < k; ++i) {
      float category_start = min_value + i * w;
      float category_end = category_start + w;
      float xi = (category_start + category_end) / 2;
  
      int fi = 0;
      for (int j = 0; j < n; ++j) {
          if (data[j] >= category_start && data[j] < category_end) {
              ++fi;
          }
      }
  
      if (fi > max_freq) {
          max_freq = fi;
          modes.clear();
          modes.push_back(xi);
      } else if (fi == max_freq) {
          modes.push_back(xi);
      }
    
   		// Calculate and display the table entries
		for (int i = 0; i < k; ++i) {
		    float category_start = min_value + i * w;
		    float category_end = category_start + w;
		    float xi = (category_start + category_end) / 2;
		
		    // Calculate the frequency (number of data points in the group)
		    int fi = 0;
		    for (int j = 0; j < n; ++j) {
		        if (data[j] >= category_start && data[j] < category_end) {
		            ++fi;
		        }
		    }
		    // Calculate cumulative frequency (cf) and cumulative relative frequency (crf)
		    cf += fi;
		    crf = static_cast<float>(cf) / n;

		    // Update arrays for fi, xi, and gi
		    fi_values[i] = fi;
		    xi_values[i] = xi;
		    gi_values[i] = crf;
		
		    // Find lmed, fm, and gm
		    if (crf >= 0.5 && fm == 0) { // Only update lmed and fm once
		        lmed = category_start; // Minimum value of the category
		        fm = fi; // Frequency of the category
		    }
		    
		
		}
		// Calculate gm separately
		for (int i = 0; i < k; ++i) {
		    if (gi_values[i] < 0.5 && gi_values[i] > gm) { // gm is the highest gi before crf >= 0.5
		        gm = gi_values[i];
		}
}    
  }

	// Display the mode(s)
	  cout << "Mode(s): ";
	  for (float mode : modes) {
	      cout << mode << ", ";
	  }
	
	// Calculate the mean (average)
	  float sum = 0;
	  for (int i = 0; i < n; ++i) {
	      sum += data[i];
	  }
	  float mean = sum / n;
	  
	  cout << "\nMean (Average): " << mean;
	      cout << "  Sum of xi: " << sum << endl;
	

	// Find lmed and fm
	for (int i = 0; i < k; ++i) {
	    if (gi_values[i] >= static_cast<float> (n2) ) {
	        lmed = xi_values[i]; // Minimum value of the category
	        fm = fi_values[i]; // Frequency of the category
	        break; // Stop searching once we find the desired category
	    }
	    
	}
	
	// Apply the formula Median
	float result = lmed + ((static_cast<float>(n) / 2) - gm) / fm * w;
	
	cout << "\nMedian: " << fixed << setprecision(2) << result;
	cout << "(Variables):\nLmedian : " << lmed;
	cout << "  fm: " << fm;
	cout << "  gm-1: " << gm;
	  
 // Calculate the sum of fixi and fixi^2
    float sum_fixi = 0;
    float sum_fixi_squared = 0;
    for (int i = 0; i < n; ++i) {
        sum_fixi += fi_values[i] * xi_values[i];
        sum_fixi_squared += fi_values[i] * xi_values[i] * xi_values[i];
    }
    // Calculate the variance
    float variance = (sum_fixi_squared - pow(sum_fixi, 2) / n) / (n - 1);
	cout << "  range: " << r << endl;
	cout << "Variance: " << variance;
    cout << "Sum of fixi: " << sum_fixi;
	cout << "  Sum of fixi^2: " << sum_fixi_squared << "\n";

    return 0;
}