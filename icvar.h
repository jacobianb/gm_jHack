#pragma once

struct Color
{
	unsigned char color[4];
	float fCol[4];
	int r, g, b, a;
	bool rainbow;

	Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
		color[0] = R;
		color[1] = G;
		color[2] = B;
		color[3] = A;
		r = R; g = G; b = B; a = A;
		fCol[0] = (float)R / 255.f; fCol[1] = (float)G / 255.f; fCol[2] = (float)B / 255.f; fCol[3] = (float)A / 255.f;
		rainbow = false;
	}
	Color(unsigned char R, unsigned char G, unsigned char B) {
		color[0] = R;
		color[1] = G;
		color[2] = B;
		color[3] = 255;
		r = R; g = G; b = B; a = 255;
		fCol[0] = (float)R / 255.f; fCol[1] = (float)G / 255.f; fCol[2] = (float)B / 255.f; fCol[3] = 1.f;
		rainbow = false;
	}
	bool operator == (const Color& other)
	{
		return fCol[0] == other.fCol[0] && fCol[1] == other.fCol[1] && fCol[2] == other.fCol[2] && fCol[3] == other.fCol[3];
	}
	bool operator != (const Color& other)
	{
		return !(*this == other);
	}
	static Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}
	// wip
	/*void RandomizeIfNeeded()
	{
		if (rainbow)
		{
			static float rainbowFl;
			rainbowFl += 0.005f;
			if (rainbowFl > 1.f) rainbowFl = 0.f;
			*this = FromHSB(rainbowFl, 1.f, 1.f);
		}
	}*/
};

class ICvar
{
public:
	/*0*/	virtual void Connect(void* (*)(char const*, int*)) = 0;
	/*1*/	virtual void Disconnect(void) = 0;
	/*2*/	virtual void* QueryInterface(char const*) = 0;
	/*3*/	virtual void* Init(void) = 0;
	/*4*/	virtual void Shutdown(void) = 0;

	/*5*/	virtual void* Nothing1(void) = 0;
	/*6*/	virtual void* Nothing2(void) = 0;
	/*7*/	virtual void* Nothing3(void) = 0;
	/*8*/	virtual void* Nothing4(void) = 0;

	/*10*/	virtual void* AllocateDLLIdentifier(void) = 0;
	/*11*/	virtual void RegisterConCommand(void*) = 0;
	/*12*/	virtual void UnregisterConCommand(void*) = 0;
	/*13*/	virtual void UnregisterConCommands(int) = 0;
	/*14*/	virtual const char* GetCommandLineValue(char const*) = 0;
	/*15*/	virtual void* FindCommandBase(char const*) = 0;
	/*16*/	virtual const void* FindCommandBase(char const*)const = 0;
	/*17*/	virtual void* FindVar(char const * var_name) = 0;
	/*18*/	virtual void* FindVar(char const* var_name)const = 0;
	/*19*/	virtual void* FindCommand(char const*) = 0;
	/*20*/	virtual void* FindCommand(char const*)const = 0;

	/*21*/	virtual void InstallGlobalChangeCallback(void (*)(void*, char const*, float)) = 0;
	/*22*/	virtual void RemoveGlobalChangeCallback(void (*)(void*, char const*, float)) = 0;
	/*23*/	virtual void CallGlobalChangeCallbacks(void*, char const*, float) = 0;
	/*24*/	virtual void InstallConsoleDisplayFunc(void*) = 0;
	/*25*/	virtual void RemoveConsoleDisplayFunc(void*) = 0;
	/*26*/	virtual void ConsoleColorPrintf(Color const&, char const*, ...)const = 0;
	/*27*/	virtual void ConsolePrintf(char const*, ...)const = 0;
	/*28*/	virtual void ConsoleDPrintf(char const*, ...)const = 0;
	/*29*/	virtual void RevertFlaggedConVars(int) = 0;
	/*30*/	virtual void InstallCVarQuery(void*) = 0;
	/*31*/	virtual bool IsMaterialThreadSetAllowed(void)const = 0;
	/*32*/	virtual void QueueMaterialThreadSetValue(void*, char const*) = 0;
	/*33*/	virtual void QueueMaterialThreadSetValue(void*, int) = 0;
	/*34*/	virtual void QueueMaterialThreadSetValue(void*, float) = 0;
	/*35*/	virtual bool HasQueuedMaterialThreadConVarSets(void)const = 0;
	/*36*/	virtual void ProcessQueuedMaterialThreadConVarSets(void) = 0;
	/*37*/	virtual void FactoryInternalIterator(void) = 0;
};