# Course: CSCI-330      Assignment #7      Semester: Fall 2020  
#                                                               
# NAME:Carlos Sanchez   Z-ID: z1729554             
#                                                               
# TA's Name: Gude Venkata Sai Haswanth                                    
#                                                             
# Due: Friday 11/06/2020 by 11:59PM                                    

BEGIN {
#Header for the output	
	FS = ":"
	printf("%-17s\t%-15s\t%13s\n", "Name", "Position", "Sales Amount")
	print "======================================================"
      }
#Each record is sent to the appropriate section, and put into the appropriate array

#Product Record
NF==4{
	productcat[$1]=$2
	productdesc[$1]=$3
	productprice[$1]=$4
     }

#Associate Record
NF==3 {
	split($2,name," ")
	associatename[$1]=name[2]", "name[1]
	associatepos[$1]=$3
	associatetotsale[$1]=0.00
      }

#Sales Record
NF==5 {
	saledate[$1]=$4

	#Simple loop to add up sales
	counter=0
	while (counter < $3)
       	{
		associatetotsale[$5]+=productprice[$2]
		counter++
        }
      }

END {
        #loop will print out sales in descending order
	for (i in associatetotsale)
       	{
		printf("%-20s\t%-15s\t%10.2f\n", associatename[i], associatepos[i], associatetotsale[i]) | "sort -nr -k 4"
	}
    }    
