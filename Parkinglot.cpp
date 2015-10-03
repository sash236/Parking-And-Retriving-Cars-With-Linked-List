/***********************
/*
/* Compiler Visual Studio 6, EE
/* Parking lot simulation.
/*
/* This program creates two alleys (stacks) to park and retrieve cars.
/*
/* CarNode : A class for one node of linked list. One node represents a car and its relative position in the parking alley.
/*
/* Alley: A class for the stack of nodes. Two instantiations A and B are used.
/*
/***********************/
#include <iostream>	
#include <ctype.h>
#include <iomanip>
using namespace std;

enum MenuSelect {DISPLAY, RETRIEVE, PARK, QUIT};

#define MAXSIZE 5

class CarNode {
	public:
		CarNode() : m_pNext(0), m_ticketNum(0) {}
		~CarNode(){}
//		CarNode(CarNode &): m_pNext(0), m_ticketNum(0) { }

		// assign next pointer
		void SetNext(CarNode* p){m_pNext=p;}

		// assign ticket number
		void SetTicketNum(int tN){m_ticketNum=tN;}

		// get the next pointer
		CarNode *GetNext(void){return(m_pNext);}

		// get the ticket number
		int GetTicketNum(void){return(m_ticketNum);}

	private:
		int m_ticketNum; 	// ticket number of car 
		CarNode *m_pNext; 	// pointer to next node in stack 
}; 		


		
class CAlley {
	public:
		CAlley () : m_pTop(0), mSize(0), mMaxSize(MAXSIZE) { }
		~CAlley () {}
		CAlley (CAlley &):m_pTop(0), mSize(0), mMaxSize(MAXSIZE) { }
		int Park(int); // park a car

		void Retrieve(int, CAlley *); // retrieve a car
		void Terminate(); // quit the program
		void Display(char *); // display contents af alley 

	private:
		void SetTop(CarNode *p){m_pTop=p;} // assign top pointer

		// check if stack is empty
		bool Empty(){return ((mSize==0) ? true : false);}

		// check if stack is full
		bool Full() {return ((mSize==MAXSIZE) ? true : false);}

		int Push(CarNode *); // push one node onto top of stack

		CarNode * Pop(); // pop one node from the top of stack

		CarNode *m_pTop; 	// pointer to top of Allay (stack) 
		int mSize; 	// number of nodes in Allay (stack) 
		int mMaxSize; 	//max number of nodes in Allay (stack) 
}; 


class CMenu {

	public:
		void Intro();
		int EnterTicketNum();
		MenuSelect GetInput();

	private:
		char m_cInput;

};
		
/************
* Function: CMenu::Intro()
* Purpose: 
*		Prints the intriductory instruction to the user.
* 
* Parameters: 
*
* Local Variables: 
*
*
************/
void CMenu::Intro()
{
/*                                                                        */
/* Print introduction of what this program is all about.                  */
/*                                                                        */
	cout << "\nThis program simulates the operations of a parking lot.  \n";


}



/************
* Function: CAlley::Terminate()
* Purpose: 
*		Prints the intriductory instruction to the user.
* 
* Parameters: 
*
* Local Variables: 
*
*
************/
void CAlley::Terminate()
{
/*                                                                        */
/* If the user has entered  'q' or 'Q' (to terminate the program),        */
/* this functions quits the program.                                      */
/*                                                                        */
	
	cout << "Exiting .. one moment ... done! \n";
	return;

}


/************
* Function: CMenu::GetInput
* Purpose: 
*		Getting Valid Character Input
* 
* Parameters: 
*
* Local Variables: 
*		char cInput: holds the user entered data.
*
*
************/
MenuSelect CMenu::GetInput()
{

	char cInput[1] = "";

	for (;;) // infinite for loop
	{
	// executed one or more times

	cout << "\nEnter your input below ..."; 
	cout << "\n"  <<"   " << "D)isplay";
	cout << "   " <<  "P)ark";
	cout << "   " <<  "R)etrieve";
	cout << "   " <<  "Q)uit:    ";

	cin >> cInput;
//	cout << "\nTime to Validate input\n";


	 	if(cin.good())
		{
//			cout << " User Input:  " << cInput ;

			if( !strcmpi(cInput,"d") )
			{
				cin.clear();
				cin.ignore(120, '\n');
				return DISPLAY;
			}

			else if(!strcmpi(cInput,"r") )//
			{
				cin.clear();
				cin.ignore(120, '\n');
				return RETRIEVE;
			}
			else if(!strcmpi(cInput,"p") )//
			{
				cin.clear();
				cin.ignore(120, '\n');
				return PARK;
			}
			else if(!strcmpi(cInput,"q") )//
			{
				cin.clear();
				cin.ignore(120, '\n');
				return QUIT;
			}
			else
			{
				cout << "\nPlease select one of the menu options!\n";
				cin.clear();
				cin.ignore(120, '\n');

			}

		}// end if cin.good()

	} // end for loop

}



/************
* Function: CMenu::EnterTicketNum
* Purpose: 
*		Getting Valid Numeric Input
* 
* Parameters: 
*
* Local Variables: 
*		int nInput: holds the user entered data.
*
*
************/
int CMenu::EnterTicketNum()
{

	int nInput = 0;

	for (;;) // infinite for loop
	{
	// executed one or more times
	cout << "\nEnter your Ticket no: "; 
	cin >> nInput;

	// if numbers entered, enter the block
		if (cin.good()) { 

/*                                                                        */                                                       
/*    Validity check for input: Must be a positive odd integer < 13.      */
/*                                                                        */

			if (nInput <= 0)	{
				cout << "Sorry, but the integer has";
				cout << " to be positive.\n";
				}
			else 
				break;

		} // end if cin.good()


		else if (!isdigit(nInput))
		cout << "Only digits are valid!\n";

		cin.clear();   //  executed zero or more times
		cin.ignore(120, '\n'); // executed zero or more times

	} // end for loop

	return(nInput);
}



////////////////////////////////////////////////////////////////
// Function: CAlley::Push

// Purpose: Add a new node to top of stack

// Parameters: 

// CarNode * pNewNode- the node to be added to top of stack

// Local Variables:

// status - return 1 if pushed sucessfully

// - return 0 if stack was full 

////////////////////////////////////////////////////////////////

int CAlley::Push(CarNode* pNewNode)

{
	SetTop(pNewNode);					// Sets the top pointer to the last parked Car


//	pNewNode->m_pTop = 0;
	return(1);
}



///////////////////////////////////////////////////////////////

// Function: CAlley::Park ( )

// Purpose: Park a car, if lot is not full. First allocate a
// node, then add it to the top of the stack

// Parameters: 

// userTicketNum - the ticket number for the node to be added

// Local Variables:

// 	CarNode *pNewNode	 - local pointer to newly allocated node 
// 	int status	 - 1 if parked sucessfully (lot not full) 
// 		0 if not parked (lot was full) 

///////////////////////////////////////////////////////////////

int CAlley::Park(int userTicketNum)

{

	CarNode *pNewNode;						// assign local CarNode	

	pNewNode = new CarNode;					// initializes local CarNode
//	cout << "   m_pNext Begin = "<< pNewNode->GetNext() << endl;
	if(Full()) { 
		cout << "            PARKING LOT FULL\n" ;
	}

	else {
//		cout << "\nThere is still room for " << 4-mSize << " Cars!" ;
		cout << " Ticket no. = "<< userTicketNum ;		  // Issues the Ticket no
		pNewNode->SetTicketNum(userTicketNum);					// assign the Ticket no
		
		if (mSize > 0) {
			pNewNode->SetNext(m_pTop);							// assign the next pointer
		}

		Push(pNewNode);											// add a new node to the top of the stack
		mSize++;												// increments the node size, # of Cars parked
		cout << "      Parked Successfully!" << endl;
	};
//	cout << "   mSize End= "<< mSize << endl;

	int status = !Full();  // so it will return a "1" if lot not full
						//    &  will return a "0" if lot is full
	return (status); // returns according to the spec
					  
}


/////////////////////////////////////////////////////////////////

// Function: CAlley::Pop

// Purpose: Remove a node to top of Allay (stack). 

// Parameters: 

// CarNode * pNewNodeB - returns the node removed from top of Alleay
// is zero if stack is empty
// tkN - ticket no of Alley A

// Local Variables:

/////////////////////////////////////////////////////////////////

CarNode * CAlley::Pop()

{

	CarNode *pCurr, *pNewNodeB,*pDelete = 0;			// assign local CarNode	

	pCurr = m_pTop;	
	pNewNodeB = new CarNode;					// initializes local CarNode
	int tkN = m_pTop->GetTicketNum();			// Gets the Alley A's ticket no
	pNewNodeB->SetTicketNum( tkN ); // Alley A's ticket no is assigned to the the new node


/* The following 3 lines essentially pops off the top */

	pCurr =  m_pTop->GetNext() ;			//  Evaluates the next pointer
	m_pTop = pCurr; 						// assigns it to top pointer
	mSize--;								// delete the Car from Alley A

	return(pNewNodeB);
}

///////////////////////////////////////////////////////////////

// Function: CAlley:: Retrieve ( int userTicketNum, CAlley *pB)

// Purpose: Retrieve a car from alley A. Search for the car/node 
// based on ticket num. by driving a car (popping off top) out of
// A and driving (pushing onto top) into B.

// If the car is found, it is not pushed onto B, but rather, 
// it is deleted. Then the cars in B are moved back into A.

// Parameters: 

// userTicketNum - the ticket number for the node to be added
// pB -pointer to CAlley B 

// Local Variables:
// CarNode *pCurr, *pDelete, *pCurrB  - local pointer used as index
// int found - 1 if car is found, 0 if not found

///////////////////////////////////////////////////////////////

void CAlley::Retrieve(int userTicketNum, CAlley *pB)

{

	CarNode *pCurr = 0, *pDelete = 0, *pCurrB = 0;	// assign local CarNode
	pCurr = m_pTop;								// moves the current pointer to next parked Car


  while (mSize > 0) // while (mSize > 0) loop 
  {
	// executed one or more times

	if ( userTicketNum == m_pTop->GetTicketNum() ) {
		cout << "\n Car found in Alley A";
		int found = 1;
		pDelete = pCurr;
		pCurr =  m_pTop->GetNext() ;
		m_pTop = pCurr; 
		mSize--;

		while ( pB->mSize > 0 ) {
			cout << "\n Cars found in B .. need to move them ...";
			int tkN = (pB->m_pTop)->GetTicketNum()  ;
			pB->m_pTop = (pB->m_pTop)->GetNext();
			Park( tkN );
			pB->mSize--;
		}

		return ;
	} // if ( userTicketNum == ... loop

	else {
		pCurrB = Pop();
		if (pB->mSize > 0) {
			pCurrB->SetNext(pB->m_pTop);					// assign the next pointer
		}
		pB->Push( pCurrB );
		pB->mSize++;

	} // else loop for pop()


  } // end - if (mSize > 0) loop


  if ( (mSize == 0) && (pB->mSize > 0) ) {

	  cout << "\n CAR NOT PARKED IN MY LOT " << endl;

		while ( pB->mSize > 0 ) {
			cout << "\n Cars found in B .. need to move them ...";
			int tkN = (pB->m_pTop)->GetTicketNum()  ;
			pB->m_pTop = (pB->m_pTop)->GetNext();
			Park( tkN );
			pB->mSize--;
		}

  }

}



////////////////////////////////////////////////////////////////
// Function: CAlley::Display

// Purpose: Add a new node to top of stack

// Parameters: 
//		Alley name is being passed on

// Local Variables:
//		int k			- local int 
//		CarNode CurrP - local CarNode


////////////////////////////////////////////////////////////////

void CAlley::Display(char *AlleyName)
{


	cout << AlleyName ;							// Gets the first car's ticket no

  if (mSize > 0) {

	cout << ":   " << m_pTop->GetTicketNum() ;   // Prints the first car's ticket no

	CarNode *CurrP = 0;							// assign local CarNode
	CurrP = m_pTop;								// moves the current pointer to next parked Car

	int k = mSize -1;

	while (k!=0) {
		CurrP = CurrP->GetNext() ;				// moves the current pointer to next parked Car
		cout << "   " << CurrP->GetTicketNum() ; // Prints the subsequent parked car's ticket no
		k--;
	}
  }

  else {
	cout << ":   " << "Parking lot is Empty!" ;
  }


	cout << endl;	
}



/************
* Function: main
* Purpose: 
*		Process the Parkinglot Simulator
* 
* Parameters: 
*		Fuction GetInput: get the valid user input. Fuction Init: Initialize the variables. 
*		Fuction Calculate: Calcualtes the array values. Fuction Display: Prints the Matrix on the screen
*
* Local Variables: 
*		Class type UData refers to user entered data.
*		int tN, utN, rValue ;
*		Enum type cUInput ;
*		pB pointer class Alley B
*
************/

void main()
{

	int tN = 0, utN = 0, rValue = 1;
	MenuSelect cUInput = QUIT;

	CMenu UData;
	CAlley AlleyA, AlleyB ;
	CAlley *pB = &AlleyB ;


	UData.Intro();

	for (;;) // infinite for loop
	{
		// executed one or more times
		cUInput = UData.GetInput();

		switch (cUInput) {
		case DISPLAY:
			cout << "\nDisplaying the contents of Alley A ...\n";
			AlleyA.Display("Alley A");
			break;
		case RETRIEVE:
			cout << "Retrieve a car ...\n";
			utN = UData.EnterTicketNum();
			AlleyA.Retrieve(utN, pB);
			break;
		case PARK:
			cout << "\nPark a car ...     ";
			rValue = AlleyA.Park(++tN);
			if (rValue == 1) {
//				cout << "      Parked Successfully!" << endl;
			}
			break;
		case QUIT:
			cout << "\nQuiting the program ...    ";
			AlleyA.Terminate();
			exit(0);
		default:
			cerr << "Invalid Entry\n";
			break;

		}

	}   /* End of for input>-1 loop */

}
