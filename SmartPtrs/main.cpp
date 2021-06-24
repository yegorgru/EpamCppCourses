#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "MyUnique_ptr.h"
#include "CObject.h"

#include <memory>

TEST_CASE("testing MyUnique_ptr") {
	{
		MyUnique_ptr p1;
		CHECK(!p1);
		CHECK(p1.get() == nullptr);
		p1.release();
		CHECK(!p1);
		CHECK(p1.get() == nullptr);
		p1.reset();
		CHECK(!p1);
		CHECK(p1.get() == nullptr);
	}
	{
		auto d = new DerivedObject;
		MyUnique_ptr empty, from_reset, from_ctor(d);
		from_reset.reset(d);
		CHECK(from_reset);
		CHECK(from_ctor);
		CHECK(from_reset == from_ctor);

		CHECK(from_reset.get() == from_ctor.get());
		CHECK(from_reset.get() != empty.get());
		empty = make_unique<DerivedObject>();
		CHECK(from_reset.get() == from_ctor.get());
		CHECK(from_reset.get() != empty.get());
		from_ctor.release();
		CHECK(!from_ctor);
	}
	{
		MyUnique_ptr p1(new CObject);
		auto cObjectPtr = p1.get();
		MyUnique_ptr p2(std::move(p1));
		CHECK(p2.get() == cObjectPtr);
		CHECK(!p1);
		p1 = std::move(p2);
		CHECK(p1.get() == cObjectPtr);
		CHECK(!p2);

		p2 = make_unique<DerivedObject>("a", 5);
		auto cObjectPtr2 = p2.get();
		CHECK(p1.get() == cObjectPtr);
		CHECK(p2.get() == cObjectPtr2);
		p1.swap(p2);
		CHECK(p1.get() == cObjectPtr2);
		CHECK(p2.get() == cObjectPtr);
	}
	{
		MyUnique_ptr p1(new CObject);
		MyUnique_ptr p2(new DerivedObject);
		CHECK(p1->foo() == "foo");
		CHECK((*p2).foo() == "derived foo");
	}
}