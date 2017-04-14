/* @file
 *
 * Compile with:
 * c++ --std=c++11 simpleresolver.cpp -o simpleresolver
 *
 * Simple DNS resolver using getaddrinfo to check networking settings e.g. inside small docker containers.
 * Execute with a domain name as the first argument, and the port as the second, e.g.
 *
 *     ./simpleresolver www.google.com 80
 *
 * @author Mark Grimes
 * @date 14/Apr/2017
 * @copyright MIT Licence (https://opensource.org/licenses/MIT)
 */
#include <iostream>
#include <array>
#include <netdb.h>
#include <arpa/inet.h>

int main( int argc, char* argv[] )
{
	if( argc!=3 )
	{
		std::cerr << "Error! Requires exactly 2 arguments of the address and service\n";
		return -1;
	}

	std::cout << "looking up " << argv[1] << ":" << argv[2] << std::endl;
	addrinfo* pAddrResult=nullptr;
	int result=getaddrinfo( argv[1], argv[2], nullptr, &pAddrResult );
	if( result!=0 )
	{
		std::cerr << "Error! getaddrinfo returned '" << gai_strerror(result) << "'\n";
		return -2;
	}

	for( addrinfo* pCurrentResult=pAddrResult; pCurrentResult!=nullptr; pCurrentResult=pCurrentResult->ai_next )
	{
		std::array<char,256> buffer{ "failed to resolve address" };
		if( pCurrentResult->ai_addr->sa_family==AF_INET ) inet_ntop( AF_INET, &reinterpret_cast<sockaddr_in*>(pCurrentResult->ai_addr)->sin_addr, buffer.data(), buffer.size() );
		else if( pCurrentResult->ai_addr->sa_family==AF_INET6 ) inet_ntop( AF_INET6, &reinterpret_cast<sockaddr_in6*>(pCurrentResult->ai_addr)->sin6_addr, buffer.data(), buffer.size() );
		std::cout << "Got the result '" << buffer.data() << "'\n";
	}

	freeaddrinfo(pAddrResult);
}
