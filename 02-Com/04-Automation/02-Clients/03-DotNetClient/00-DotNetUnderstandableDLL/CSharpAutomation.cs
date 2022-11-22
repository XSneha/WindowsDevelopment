//cmd : csc.exe /r:AutomationSetrverTypeLibForDLL.dll CSharpAutomation.cs

using System;
using System.runtime.iteropServices;
using AutomationServerTypelibForDotNet;

class {
public static void Main()
{
	//code
	CMyMathClass objCMyMathClass = new CMyMathClass() ;
	objIMyMathc= (IMyMath)	objCMyMathClass;
	int num1,num2,sum,sub;
	num1 = 75;
	num2 = 135;
	sum = objIMyMath.sumOfTwoIntegers(num1,num2);
	console.writeline("Sum of "+num1 +" and "+num2+ " is "+sum); 

	sun= objIMyMath.subtractionOfTwoIntegers(num1,num2);
	console.writeline("Subtraction of "+num1 +" and "+num2+ " is "+sub); 
}
}