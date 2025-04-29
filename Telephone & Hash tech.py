class CollusionHandling:
    def __init__(self):
        self.linearHash=[]
        self.quadraticHash=[]
        self.linearCount=0
        self.quadraticCount=0
        self.bucketSize=0

    def create_bucket(self, bsize):
        self.bucketSize=bsize
        self.linearHash=list(None for i in range(self.bucketSize))
        self.quadraticHash=list(None for i in range(self.bucketSize))

    def has_key(self, key):
        return key % self.bucketSize

    def linear_Probing(self,name,phoneNo):
        index=0
        pos=self.has_key(phoneNo)
        print("Pos is:",pos)
        if self.linearHash[pos] == None:
            self.linearHash[pos]={name:phoneNo}
        else:
            index=(pos+1)%self.bucketSize
            while index != pos:
                if self.linearHash[index]==None:
                    self.linearHash[index]={name:phoneNo}
                    return index
                index =  (index+1)%self.bucketSize
            return -1

    def search_key_Linear_prob(self,phoneNo):
        index=0
        self.linearCount=0
        pos=self.has_key(phoneNo)
        recFound=False
        phone=0
        if self.linearHash[pos] != None:
            self.linearCount += 1
            for phone in self.linearHash[pos].values():
                if phone==phoneNo:
                    print("Phone number is in Table at position ",pos)
                    recFound=True
                else:
                    index=(pos+1)%self.bucketSize
                    while index != pos:
                        self.linearCount += 1 
                        if self.linearHash[index] != None: 
                            for phone in self.linearHash[index].values():
                                if phone==phoneNo:
                                    print("Phone number is in Table at position ",index)
                                    recFound=True
                        index =  (index+1)%self.bucketSize
        if not recFound:
            print("Phone number not found!!")
        print("Number of records searched in table to find a key is :",self.linearCount)

    def display_Linear_Hash_Table(self):
        name=None
        for i in range(self.bucketSize):
            if self.linearHash[i]==None:
                print (i," ",None)
            else:
                print(i, self.linearHash[i])

    def quadratic_Probing(self,name,phoneNo):
        index=0
        pos=self.has_key(phoneNo)
        print("Pos is:",pos)
        if self.quadraticHash[pos] == None:
            self.quadraticHash[pos]={name:phoneNo}
        else:
            i=1
            index=pos+i*i
            while index != pos:
                print("Index:",index)
                if self.quadraticHash[index]==None:
                    self.quadraticHash[index]={name:phoneNo}
                    return index
                i+=1
                index =  (pos+i*i)%self.bucketSize
            return -1

    def search_key_quadratic_prob(self,phoneNo):
        index=0
        self.quadraticCount=0
        pos=self.has_key(phoneNo)
        recFound=False
        phone=0
        if self.quadraticHash[pos] != None:
            self.quadraticCount +=1
            for phone in self.quadraticHash[pos].values():
                if phone==phoneNo:
                    print("Phone number is in Table at position ",pos)
                    recFound=True
                else:
                    i=1
                    index=(pos+i*i)%self.bucketSize
                    while index != pos:
                        self.quadraticCount += 1 
                        if self.quadraticHash[index] != None:
                            for phone in self.quadraticHash[index].values():
                                if phone==phoneNo:
                                    print("Phone number is in Table at position ",index)
                                    recFound=True
                        i+=1
                        index =  (pos+i*i)%self.bucketSize
        if not recFound:
            print("Phone number not found!!")
        print("Number of records searched in table to find a key is :",self.quadraticCount)

    def display_quadratic_Hash_Table(self):
        name=None
        for i in range(self.bucketSize):
            if self.quadraticHash[i]==None:
                print (i," ",None)
            else:
                print(i, self.quadraticHash[i])

c1=CollusionHandling()

bsize=int(input("Enter the Size of hash table:"))
c1.create_bucket(bsize)

choice1=0
while (choice1 !=3):
    print("\n*******Collusion Handling Techniques*******")
    print("\n1. Linear Probing")
    print("\n2. Quadratic Probing")
    print("\n3. Exit Application")
    choice1=int(input("Enter Your Choice:"))
    if choice1==1:
        choice2=0
        while choice2 !=4:
            print("\n*******Linear Probing Techniques*******")
            print("\n1. Add Record in Table")
            print("\n2. Display Table Contents")
            print("\n3. Search Telephone in Table")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            if choice2 ==1:
                name=input("Enter the name of a person:")
                phoneNo = int(input("Enter phone number:"))
                result=c1.linear_Probing(name,phoneNo)
                if result == -1:
                    print("\nTable is Full!")
            elif choice2 == 2:
                c1.display_Linear_Hash_Table()
            elif choice2==3:
                phoneNo=int(input("Enter the phone number to be searched::"))
                c1.search_key_Linear_prob(phoneNo)
            elif choice2 == 4:
                break
    elif choice1 ==2:
        choice2=0
        while choice2 !=4:
            print("\n*******Quadratic Probing Techniques*******")
            print("\n1. Add Record in Table")
            print("\n2. Display Table Contents")
            print("\n3. Search Telephone in Table")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            if choice2 ==1:
                name=input("Enter the name of a person:")
                phoneNo = int(input("Enter phone number:"))
                result=c1.quadratic_Probing(name,phoneNo)
                if result == -1:
                    print("\nTable is Full!")
            elif choice2 == 2:
                c1.display_quadratic_Hash_Table()
            elif choice2==3:
                phoneNo=int(input("Enter the phone number to be searched::"))
                c1.search_key_quadratic_prob(phoneNo)
            elif choice2 == 4:
                break
    elif choice1 ==3:
        break
