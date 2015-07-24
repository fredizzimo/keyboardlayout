#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "NonDominatedSet.hpp"
#include <array>
#include "TestUtilities.hpp"
#include "MakeArray.hpp"
using namespace testing;

template<typename KeyboardArray, typename SolutionArray, typename SolutionsVector>
void testEqual(const KeyboardArray& expectedKeyboards, const SolutionArray& expectedSolutions, 
	const SolutionsVector& actual)
{
	ASSERT_EQ(expectedKeyboards.size(), actual.size());
	ASSERT_EQ(expectedSolutions.size(), actual.size());
	auto sortedSolutions = actual;
	std::sort(sortedSolutions.begin(), sortedSolutions.end(), [](const auto& lhs, const auto& rhs)
	{
		return lhs.m_solution < rhs.m_solution;
	});
	auto ek = std::begin(expectedKeyboards);
	auto es = std::begin(expectedSolutions);
	for (auto&& i : actual)
	{
		EXPECT_EQ(*ek, i.m_keyboard);
		
		auto si = std::begin(*es);
		for (auto&& j : i.m_solution)
		{
			EXPECT_EQ(*si, j);
			++si;
		}
		++ek;
		++es;
	}
}
template<size_t Size>
using KeyboardArray = std::array<Keyboard<1>, Size>;
template<size_t Size, size_t NumDimensions = 1>
using SolutionArray = std::array<std::array<float, NumDimensions>, Size>;

TEST(NonDominatedSetTests, SimpleOneDimensionalOneValue)
{
	KeyboardArray<1> keyboards{ Keyboard<1>({1}) };
	SolutionArray<1> solutions{ {1.0} };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	testEqual(keyboards, solutions, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(1.0f));
}

TEST(NonDominatedSetTests, OneDimensionalTwoValues)
{
	KeyboardArray<2> keyboards{ Keyboard<1>({1}), Keyboard<1>({2}) };
	SolutionArray<2> solutions{ 1.0, 2.0 };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	testEqual(KeyboardArray<1>{ Keyboard<1>({2}) }, SolutionArray<1>{ {2.0} }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(2.0f));
}
TEST(NonDominatedSetTests, OneDimensionalTwoDifferentOrder)
{
	KeyboardArray<2> keyboards{ Keyboard<1>({2}), Keyboard<1>({1}) };
	SolutionArray<2> solutions{ 2.0, 1.0 };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	testEqual(KeyboardArray<1>{ Keyboard<1>({2}) }, SolutionArray<1>{ {2.0} }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(2.0f));
}

TEST(NonDominatedSetTests, OneDimensionalThreeValues1)
{
	using A = std::pair<Keyboard<1>, std::array<float, 1>>;
	A a = { Keyboard<1>({1}), { 1.0f } };
	A b = { Keyboard<1>({2}), { 2.0f } };
	A c = { Keyboard<1>({3}), { 3.0f } };
	KeyboardArray<3> keyboards{ a.first, b.first, c.first };
	SolutionArray<3> solutions{ a.second, b.second, c.second };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	testEqual(KeyboardArray<1>{ c.first }, SolutionArray<1>{ c.second }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(3.0f));
}

TEST(NonDominatedSetTests, OneDimensionalThreeValues2)
{
	using A = std::pair<Keyboard<1>, std::array<float, 1>>;
	A a = { Keyboard<1>({1}), { 1.0f } };
	A b = { Keyboard<1>({2}), { 2.0f } };
	A c = { Keyboard<1>({3}), { 3.0f } };
	KeyboardArray<3> keyboards{ a.first, b.first, c.first };
	SolutionArray<3> solutions{ a.second, b.second, c.second };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	testEqual(KeyboardArray<1>{ c.first }, SolutionArray<1>{ c.second }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(3.0f));
}

TEST(NonDominatedSetTests, OneDimensionalThreeValues3)
{
	using A = std::pair<Keyboard<1>, std::array<float, 1>>;
	A a = { Keyboard<1>({1}), { 1.0f } };
	A b = { Keyboard<1>({2}), { 2.0f } };
	A c = { Keyboard<1>({3}), { 3.0f } };
	KeyboardArray<3> keyboards{ a.first, b.first, c.first };
	SolutionArray<3> solutions{ a.second, b.second, c.second };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	testEqual(KeyboardArray<1>{ c.first }, SolutionArray<1>{ c.second }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(3.0f));
}

TEST(NonDominatedSetTests, OneDimensionalThreeValues4)
{
	using A = std::pair<Keyboard<1>, std::array<float, 1>>;
	A a = { Keyboard<1>({1}), { 1.0f } };
	A b = { Keyboard<1>({2}), { 2.0f } };
	A c = { Keyboard<1>({3}), { 3.0f } };
	KeyboardArray<3> keyboards{ a.first, b.first, c.first };
	SolutionArray<3> solutions{ a.second, b.second, c.second };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	testEqual(KeyboardArray<1>{ c.first }, SolutionArray<1>{ c.second }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(3.0f));
}

TEST(NonDominatedSetTests, OneDimensionalThreeValues5)
{
	using A = std::pair<Keyboard<1>, std::array<float, 1>>;
	A a = { Keyboard<1>({1}), { 1.0f } };
	A b = { Keyboard<1>({2}), { 2.0f } };
	A c = { Keyboard<1>({3}), { 3.0f } };
	KeyboardArray<3> keyboards{ a.first, b.first, c.first };
	SolutionArray<3> solutions{ a.second, b.second, c.second };
	NonDominatedSet<1, 1> s(keyboards, solutions);
	ASSERT_EQ(1, s.size()); 
	std::array<A, 1> res{ c };
	testEqual(KeyboardArray<1>{ c.first }, SolutionArray<1>{ c.second }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(3.0f));
}

TEST(NonDominatedSetTests, OneDimensionalThreeValues6)
{
	using A = std::pair<Keyboard<1>, std::array<float, 1>>;
	A a = { Keyboard<1>({1}), { 1.0f } };
	A b = { Keyboard<1>({2}), { 2.0f } };
	A c = { Keyboard<1>({3}), { 3.0f } };
	NonDominatedSet<1, 1> s;
	s.insert(a.first, a.second);
	s.insert(b.first, b.second);
	s.insert(c.first, c.second);
	ASSERT_EQ(1, s.size()); 
	std::array<A, 1> res{ c };
	testEqual(KeyboardArray<1>{ c.first }, SolutionArray<1>{ c.second }, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(3.0f));
}

TEST(NonDominatedSetTests, TwoDimensional)
{
	using A = std::pair<Keyboard<1>, std::array<float, 2>>;
	A a = { Keyboard<1>({1}), { 4.0f, 1.0f } };
	A b = { Keyboard<1>({2}), { 3.0f, 1.0f } };
	A c = { Keyboard<1>({3}), { 2.0f, 1.0f } };
	A d = { Keyboard<1>({4}), { 1.0f, 1.0f } };
	A e = { Keyboard<1>({5}), { 3.0f, 2.0f } };
	A f = { Keyboard<1>({6}), { 2.0f, 2.0f } };
	A g = { Keyboard<1>({7}), { 1.0f, 2.0f } };
	A h = { Keyboard<1>({8}), { 2.0f, 3.0f } };
	KeyboardArray<8> keyboards{ a.first, b.first, c.first, d.first, e.first, f.first, g.first, h.first };
	SolutionArray<8, 2> solutions{ a.second, b.second, c.second, d.second, e.second, f.second, g.second, h.second };
	// 4
	// 3   h 
	// 2 g f e
	// 1 d c b a
	//   1 2 3 4
	NonDominatedSet<1, 2> s(keyboards, solutions);
	ASSERT_EQ(3, s.size()); 
	KeyboardArray<3> keyboardRes{ a.first, e.first, h.first };
	SolutionArray<3, 2> solutionRes{ a.second, e.second, h.second };
	testEqual(keyboardRes, solutionRes, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(4.0f, 3.0f));
}

TEST(NonDominatedSetTests, TwoDimensional2)
{
	using A = std::pair<Keyboard<1>, std::array<float, 2>>;
	A a = { Keyboard<1>({1}), { 4.0f, 1.0f } };
	A b = { Keyboard<1>({2}), { 3.0f, 2.0f } };
	A c = { Keyboard<1>({3}), { 2.0f, 1.0f } };
	A d = { Keyboard<1>({4}), { 1.0f, 1.0f } };
	A e = { Keyboard<1>({5}), { 3.0f, 3.0f } };
	A f = { Keyboard<1>({6}), { 2.0f, 2.0f } };
	A g = { Keyboard<1>({7}), { 1.0f, 2.0f } };
	A h = { Keyboard<1>({8}), { 2.0f, 3.0f } };
	KeyboardArray<8> keyboards{ a.first, b.first, c.first, d.first, e.first, f.first, g.first, h.first };
	SolutionArray<8, 2> solutions{ a.second, b.second, c.second, d.second, e.second, f.second, g.second, h.second };
	// 4
	// 3   h e
	// 2 g f b
	// 1 d c   a
	//   1 2 3 4
	NonDominatedSet<1, 2> s(keyboards, solutions);
	ASSERT_EQ(2, s.size()); 
	std::array<A, 2> res{ a, e };
	KeyboardArray<2> keyboardRes{ e.first, a.first };
	SolutionArray<2, 2> solutionRes{ e.second, a.second };
	testEqual(keyboardRes, solutionRes, s.getResult());
	EXPECT_THAT(s.getIdealPoint(), ElementsAreClose(4.0f, 3.0f));
}

TEST(SelectPivotPointTests, SelectPivotPoint)
{
	auto a = make_array(-2.0f, -8.0f);
	auto b = make_array(-2.0f, -5.0f);
	auto c = make_array(-3.0f, -9.0f);
	auto d = make_array(-4.0f, -6.0f);
	auto e = make_array(-4.0f, -4.0f);
	auto f = make_array(-5.0f, -7.0f);
	auto g = make_array(-6.0f, -4.0f);
	auto h = make_array(-7.0f, -6.0f);
	auto i = make_array(-7.0f, -2.0f);
	auto j = make_array(-8.0f, -8.0f);
	auto k = make_array(-8.0f, -3.0f);
	auto l = make_array(-9.0f, -1.0f);
	std::vector<std::array<float, 2>> solutionVector{ a, b, c, d, e, f, g, h, i, j, k, l };
	nondominatedset_detail::selectPivoitPoint(solutionVector);
	EXPECT_THAT(solutionVector, ElementsAre(e, l, k, i, b));
}

TEST(MapPointToRegionTests, MapPointToRegion2D)
{
	auto b = make_array(-2.0f, -5.0f);
	auto e = make_array(-4.0f, -4.0f);
	auto g = make_array(-6.0f, -4.0f);
	auto h = make_array(-7.0f, -6.0f);
	auto i = make_array(-7.0f, -2.0f);
	unsigned int res = nondominatedset_detail::mapPointToRegion(e, e);
	EXPECT_EQ(0b11, res);
	res = nondominatedset_detail::mapPointToRegion(e, b);
	EXPECT_EQ(0b10, res);
	res = nondominatedset_detail::mapPointToRegion(e, g);
	EXPECT_EQ(0b11, res);
	res = nondominatedset_detail::mapPointToRegion(e, h);
	EXPECT_EQ(0b11, res);
	res = nondominatedset_detail::mapPointToRegion(e, i);
	EXPECT_EQ(0b01, res);
	res = nondominatedset_detail::mapPointToRegion(h, e);
	EXPECT_EQ(0b00, res);
}