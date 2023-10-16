# include <Siv3D.hpp>

/// @brief アイテムのボタン
/// @param rect ボタンの領域
/// @param texture ボタンの絵文字
/// @param font 文字描画に使うフォント
/// @param name アイテムの名前
/// @param desc アイテムの説明
/// @param count アイテムの所持数
/// @param enabled ボタンを押せるか
/// @return ボタンが押された場合 true, それ以外の場合は false
bool Button(const Rect& rect, const Texture& texture, const Font& font, const String& name, const String& desc, int32 count, bool enabled)
{
	if (enabled)
	{
		rect.draw(ColorF{ 0.3, 0.5, 0.9, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 0.5, 0.7, 1.0 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else
	{
		rect.draw(ColorF{ 0.0, 0.4 });

		rect.drawFrame(2, 2, ColorF{ 0.5 });
	}

	texture.scaled(0.5).drawAt(rect.x + 50, rect.y + 50);

	font(name).draw(30, rect.x + 100, rect.y + 15, Palette::White);

	font(desc).draw(18, rect.x + 102, rect.y + 60, Palette::White);

	font(count).draw(50, Arg::rightCenter((rect.x + rect.w - 20), (rect.y + 50)), Palette::White);

	return (enabled && rect.leftClicked());
}

void Main()
{
	// クスリの絵文字
	const Texture texture{ U"💊"_emoji };

	// 粉の絵文字
	const Texture texture2{ U"🧂"_emoji };

	// 注射の絵文字
	const Texture texture3{ U"💉"_emoji };

	// お金の絵文字
	const Texture texture4{ U"🪙"_emoji };

	// 農場の絵文字
	const Texture farmEmoji{ U"🌿"_emoji };

	// 工場の絵文字
	const Texture factoryEmoji{ U"🏭"_emoji };

	// 都会の絵文字
	const Texture townEmoji{ U"🏙"_emoji };

	// 市場の絵文字
	const Texture marketEmoji{ U"🏪"_emoji };

	// フォント
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// クスリのクリック円
	const Circle cookieCircle{ 100, 220, 50 };

	// クスリの表示サイズ（倍率）
	double cookieScale = 1.0;

	// クスリの個数
	double cookies = 0;

	// 粉のクリック円
	const Circle powderCircle{ 100, 100, 50 };

	// 粉の表示サイズ（倍率）
	double powderScale = 1.0;

	// 粉の個数
	double powders = 0;

	// 注射のクリック円
	const Circle injectionCircle{ 100, 340, 50 };

	// 注射の表示サイズ（倍率）
	double injectionScale = 1.0;

	// 注射の個数
	double injections = 0;

	// お金のクリック円
	const Circle moneyCircle{ 100, 460, 50 };

	// お金の表示サイズ（倍率）
	double moneyScale = 1.0;

	// お金の個数
	double moneys = 0;

	// 農場の所有数
	int32 farmCount = 0;

	// 工場の所有数
	int32 factoryCount = 0;

	// 都会の所有数
	int32 townCount = 0;

	// 市場の所有数
	int32 marketCount = 0;

	// 農場の価格
	int32 farmCost = 10;

	// 工場の価格
	int32 factoryCost = 100;

	// 都会の価格
	int32 townCost = 500;

	// 市場の価格
	int32 marketCost = 10000;

	// ゲームの経過時間の蓄積
	double accumulatedTime = 0.0;

	while (System::Update())
	{
		// 粉の毎秒の生産量 (cookies per second) を計算する
		const int32 pps = (farmCount);

		// クスリの毎秒の生産量 (cookies per second) を計算する
		const int32 cps = (farmCount + factoryCount * 10);

		// 注射の毎秒の生産量 (cookies per second) を計算する
		const int32 ips = (factoryCount * 10 + townCount * 50);

		// お金の毎秒の生産量 (cookies per second) を計算する
		const int32 mps = (farmCount + factoryCount * 10 + townCount * 50 + marketCount * 1000);

		// ゲームの経過時間を加算する
		accumulatedTime += Scene::DeltaTime();

		// 0.1 秒以上蓄積していたら
		if (0.1 <= accumulatedTime)
		{
			accumulatedTime -= 0.1;

			// 0.1 秒分のクスリ生産を加算する
			cookies += (cps * 0.1);
			// 0.1 秒分の粉生産を加算する
			powders += (pps * 0.1);
			// 0.1 秒分の注射生産を加算する
			injections += (ips * 0.1);
			// 0.1 秒分のお金生産を加算する
			moneys += (mps * 0.1);
		}

		// 農場の価格を計算する
		farmCost = 10 + (farmCount * 10);

		// 工場の価格を計算する
		factoryCost = 100 + (factoryCount * 100);

		// 都会の価格を計算する
		townCost = 500 + (townCount * 500);

		// 市場の価格を計算する
		marketCost = 10000 + (marketCount * 1000);

		// クスリ円上にマウスカーソルがあれば
		if (cookieCircle.mouseOver() || powderCircle.mouseOver() || injectionCircle.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		// クスリ円が左クリックされたら
		if (cookieCircle.leftClicked())
		{
			cookieScale = 0.5;
			++cookies;
		}

		// クスリの表示サイズを回復する
		cookieScale += Scene::DeltaTime();

		if (0.8 < cookieScale)
		{
			cookieScale = 0.8;
		}

		// 粉円が左クリックされたら
		if (powderCircle.leftClicked())
		{
			powderScale = 0.5;
			++powders;
		}

		// 粉の表示サイズを回復する
		powderScale += Scene::DeltaTime();

		if (0.8 < powderScale)
		{
			powderScale = 0.8;
		}

		// 注射の表示サイズを回復する
		injectionScale += Scene::DeltaTime();

		if (0.8 < injectionScale)
		{
			injectionScale = 0.8;
		}

		// 注射円が左クリックされたら
		if (injectionCircle.leftClicked())
		{
			injectionScale = 0.5;
			++injections;
		}

		// 背景を描く
		Rect{ 0, 0, 800, 600 }.draw(Arg::top = ColorF{ 0.6, 0.5, 0.3 }, Arg::bottom = ColorF{ 0.2, 0.5, 0.3 });

		// クスリの数を整数で表示する
		font(U"{:.0f}個"_fmt(cookies)).drawAt(20, 200, 210);

		// クスリの生産量を表示する
		font(U"毎秒: {}"_fmt(cps)).drawAt(20, 200, 240);

		// 粉の数を整数で表示する
		font(U"{:.0f}個"_fmt(powders)).drawAt(20, 200, 90);

		// 粉の生産量を表示する
		font(U"毎秒: {}"_fmt(pps)).drawAt(20, 200, 120);

		// 注射の数を整数で表示する
		font(U"{:.0f}個"_fmt(injections)).drawAt(20, 200, 330);

		// 注射の生産量を表示する
		font(U"毎秒: {}"_fmt(ips)).drawAt(20, 200, 360);

		// クスリを描画する
		texture.scaled(cookieScale).drawAt(cookieCircle.center);

		// 粉を描画する
		texture2.scaled(powderScale).drawAt(powderCircle.center);

		// 注射を描画する
		texture3.scaled(injectionScale).drawAt(injectionCircle.center);

		// 農場ボタン
		if (Button(Rect{ 340, 40, 420, 100 }, farmEmoji, font, U"農場", U"P{} / 1 PPS"_fmt(farmCost), farmCount, (farmCost <= powders)))
		{
			powders -= farmCost;
			++farmCount;
		}

		// 工場ボタン
		if (Button(Rect{ 340, 160, 420, 100 }, factoryEmoji, font, U"工場", U"C{} / 10 CPS"_fmt(factoryCost), factoryCount, (factoryCost <= cookies)))
		{
			cookies -= factoryCost;
			++factoryCount;
		}

		//　都会ボタン
		if (Button(Rect{ 340, 280, 420, 100 }, townEmoji, font, U"都会", U"C{} / 50 IPS"_fmt(townCost), townCount, (townCost <= injections)))
		{
			injections -= townCost;
			++townCount;
		}

		//　市場ボタン
		if (Button(Rect{ 340, 400, 420, 100 }, marketEmoji, font, U"市場", U"C{} / 1000 CPS"_fmt(marketCost), marketCount, (marketCost <= cookies || marketCost <= injections)))
		{
			cookies -= marketCost;
			++marketCount;
		}
	}
}
