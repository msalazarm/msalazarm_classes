!Name: Marco Salazar, Date: 9/27/2020
!Purpose: Test how fast Gaussian Elimination in Fortran is compared to other languages.
!No inputs instead it calls all the gaussian eliminations in order.

!Main program that calls the function 5 times for each of the 5 values
!Prints out the time in nanoseconds for the operation to be completed in CSV format
PROGRAM gaussian_elimination
    IMPLICIT NONE
    call gauss(250)
    call gauss(250)
    call gauss(250)
    call gauss(250)
    call gauss(250)

    call gauss(500)
    call gauss(500)
    call gauss(500)
    call gauss(500)
    call gauss(500)

    call gauss(1000)
    call gauss(1000)
    call gauss(1000)
    call gauss(1000)
    call gauss(1000)

    call gauss(1500)
    call gauss(1500)
    call gauss(1500)
    call gauss(1500)
    call gauss(1500)

    call gauss(2000)
    call gauss(2000)
    call gauss(2000)
    call gauss(2000)
    call gauss(2000)

contains

!function that gives the time
!Sources: https://gcc.gnu.org/onlinedocs/gfortran/SYSTEM_005fCLOCK.html
integer(kind=8) function times()
    implicit none
    INTEGER(kind=8) :: count, count_rate, count_max
    CALL SYSTEM_CLOCK(count, count_rate, count_max)
    times = count
end function times

!function that performs gaussian elimination without partial pivoting
!Source: https://labmathdu.wordpress.com/gaussian-elimination-without-pivoting/
subroutine gauss(n)
    IMPLICIT NONE

    integer(kind=8) :: starttime,endtime
    INTEGER::n
    INTEGER::i,j,ii,jj

    REAL::s
    REAL,DIMENSION(n,n+1)::a
    REAL,DIMENSION(n)::x

    real::rand

    !Generate all of the random numbers in the array
    do ii=1,n
        do jj=1,n+1
            call random_number(rand)
            !Generate a random number [1, 1000] to avoid divide by 0 errors
            a(ii,jj) = floor(999*rand)+1
        end do
    end do
    starttime = times()

    !Do the Gaussian elimination
    DO j=1,n
        DO i=j+1,n
            a(i,:)=a(i,:)-a(j,:)*a(i,j)/a(j,j)
        END DO
    END DO

    DO i=n,1,-1
        s=a(i,n+1)
        DO j=i+1,n
            s=s-a(i,j)*x(j)
        END DO
        x(i)=s/a(i,i)
    END DO

    endtime = times()

    !print the execution time in csv format
    Print *, endtime-starttime, ","
end subroutine gauss

END PROGRAM