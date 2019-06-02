#include <unittest++/UnitTest++.h>
#include </home/user/Documents/Kursovik/Stego/stego.h>
#include </home/user/Documents/Kursovik/Stego/stego.cpp>

SUITE(HideTest)
{
	TEST(MessageOneWord) {
		CHECK_EQUAL("fffffff fffff  fff  ffff ffffff  ffff ffff fffffffff fffffff fffffff  fffff  fff ffff ffffff  ffff ffff  fffffffff fffffff  fffffff  fffff fff  ffff  ffffff ffff ffff fffffffff  fffffff  fffffff fffff  fff  ffff ffffff ffff ffff  fffffffff  fffffff fffffff  fffff  fff  ffff  ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff",
		Stego("/home/user/files/1.txt").hide("/home/user/files/one.txt"));
	}
	TEST(MessageSomeWord) {
		CHECK_EQUAL("fffffff fffff  fff ffff ffffff ffff  ffff  fffffffff  fffffff fffffff  fffff  fff ffff  ffffff  ffff  ffff  fffffffff fffffff  fffffff  fffff fff  ffff  ffffff  ffff  ffff fffffffff  fffffff  fffffff fffff fff  ffff ffffff ffff ffff fffffffff  fffffff fffffff fffff fff ffff ffffff ffff  ffff  fffffffff fffffff  fffffff  fffff fff  ffff ffffff  ffff  ffff fffffffff  fffffff  fffffff  fffff  fff ffff  ffffff  ffff  ffff fffffffff fffffff  fffffff fffff fff  ffff  ffffff ffff  ffff  fffffffff  fffffff fffffff fffff  fff  ffff ffffff  ffff ffff fffffffff  fffffff fffffff  fffff  fff ffff  ffffff  ffff  ffff fffffffff fffffff  fffffff  fffff fff ffff  ffffff  ffff  ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff",
		Stego("/home/user/files/2.txt").hide("/home/user/files/b.txt"));
	}
	TEST(MessageSymbolsNumbers) {
		CHECK_EQUAL("fffffff fffff fff  ffff ffffff ffff ffff fffffffff  fffffff fffffff fffff  fff  ffff  ffffff  ffff  ffff  fffffffff fffffff fffffff  fffff fff  ffff  ffffff  ffff ffff fffffffff fffffff  fffffff fffff  fff  ffff ffffff ffff ffff fffffffff  fffffff fffffff  fffff fff ffff ffffff ffff ffff  fffffffff fffffff  fffffff fffff fff  ffff ffffff ffff  ffff fffffffff fffffff fffffff fffff fff ffff ffffff  ffff  ffff fffffffff fffffff fffffff  fffff fff ffff  ffffff  ffff ffff fffffffff  fffffff  fffffff fffff fff  ffff  ffffff ffff  ffff  fffffffff fffffff fffffff fffff  fff  ffff  ffffff ffff ffff  fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff fffffff fffff fff ffff ffffff ffff ffff fffffffff fffffff",
		Stego("/home/user/files/3.txt").hide("/home/user/files/symb.txt"));
	}
	TEST(ContainerNotFound) {
		CHECK_THROW(Stego("/home/user/files/no.txt").hide("/home/user/files/b.txt"),stego_error);
	}
	TEST(EmptyContainer) {
		CHECK_THROW(Stego("/home/user/files/pyst.txt").hide("/home/user/files/b.txt"),stego_error);
	}
	TEST(MessageNotFound) {
		CHECK_THROW(Stego("/home/user/files/1.txt").hide("/home/user/files/no.txt"),stego_error);
	}
	TEST(EmptyMessage) {
		CHECK_THROW(Stego("/home/user/files/1.txt").hide("/home/user/files/pyst.txt"),stego_error);
	}
	TEST(MessageDoesNotFit) {
		CHECK_THROW(Stego("/home/user/files/smal.txt").hide("/home/user/files/b.txt"),stego_error);
	}
};

SUITE(ExtractTest)
{
	TEST(MessageOneWord) {
		CHECK_EQUAL("hello",Stego("/home/user/files/1.txt").extract());
	}
	TEST(MessageSomeWord) {
		CHECK_EQUAL("Good morning",Stego("/home/user/files/2.txt").extract());
	}
	TEST(MessageSymbolsNumbers) {
		CHECK_EQUAL("!?.,() 1369",Stego("/home/user/files/3.txt").extract());
	}
	TEST(ContainerNotFound) {
		CHECK_THROW(Stego("/home/user/files/no.txt").extract(),stego_error);
	}
	TEST(EmptyContainer) {
		CHECK_THROW(Stego("/home/user/files/pyst.txt").extract(),stego_error);
	}
	TEST(NoMessage) {
		CHECK_THROW(Stego("/home/user/files/nein.txt").extract(),stego_error);
	}
};

int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}
