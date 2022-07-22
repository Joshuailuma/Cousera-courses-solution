"""
Project for Week 4 of "Python Programming Essentials".
Collection of functions to process dates.

Be sure to read the project description page for further information
about the expected behavior of the program.
"""
import datetime

def days_in_month(year, month):
    """
    Inputs:
      year  - an integer between datetime.MINYEAR and datetime.MAXYEAR
              representing the year
      month - an integer between 1 and 12 representing the month

    Returns:
      The number of days in the input month.
    """

    if month == 12:
        days = datetime.date(year + 1, 1, 1) - datetime.date(year, month, 1)
    else:
        days = datetime.date(year, month + 1, 1) - datetime.date(year, month, 1)


    return days.days

#print(days_in_month(2022, 12))

def is_valid_date(year, month, day):
    """
    Inputs:
      year  - an integer representing the year
      month - an integer representing the month
      day   - an integer representing the day
      
    Returns:
      True if year-month-day is a valid date and
      False otherwise
    """

    is_year_valid = datetime.MINYEAR <= year <= datetime.MAXYEAR
    is_month_valid = 1 <= month <= 12

    if (is_year_valid) and (is_month_valid) is True:
        if 1 <= day <= days_in_month(year, month):
            return True

    return False

#print(is_valid_date(20000, 12, 9))
def days_between(year1, month1, day1, year2, month2, day2):
    """
    Inputs:
      year1  - an integer representing the year of the first date
      month1 - an integer representing the month of the first date
      day1   - an integer representing the day of the first date
      year2  - an integer representing the year of the second date
      month2 - an integer representing the month of the second date
      day2   - an integer representing the day of the second date
      
    Returns:
      The number of days from the first date to the second date.
      Returns 0 if either date is invalid or the second date is 
      before the first date.
    """

    check1 = is_valid_date(year1, month1, day1)
    check2 = is_valid_date(year2, month2, day2)

    if (check1 and check2 is True) and (datetime.date(year1, 
    month1, day1) < datetime.date(year2, month2, day2)):
        return (datetime.date(year2, month2, day2) - datetime.date(year1,
         month1, day1)).days
    else:
        return 0

print(days_between(20000, 1, 1, 2047, 8, 2))

        
def age_in_days(year, month, day):
    """
    Inputs:
      year  - an integer representing the birthday year
      month - an integer representing the birthday month
      day   - an integer representing the birthday day
      
    Returns:
      The age of a person with the input birthday as of today.
      Returns 0 if the input date is invalid of if the input
      date is in the future.
    """
    if (is_valid_date(year, month, day) == False):
        if (days_between(year, month, day, datetime.date.today().year,
        datetime.date.today().month, datetime.date.today().day) == 0):
            return 0
    else:
        return days_between(year, month, day, datetime.date.today().year,
         datetime.date.today().month, datetime.date.today().day)


#print(age_in_days(1997, 7, 9))