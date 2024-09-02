#include <iostream>
#include <string>
using namespace std;

class Pieza 
{
private:
	short fila;
	short columna;
	
public:

	Pieza() 
	{
		fila = 1; 
		columna = 1;
	}
	
	Pieza(short f, short c) 
	{
		fila = f;
		columna = c;
	}
	
	void verInfo() 
	{
		cout<<"Fila: "<<fila<<" Columna: "<<columna<<endl;
	}
	
	bool esValido(short f, short c) 
	{
		if (f >= 1 && f <= 8 && c >= 1 && c <= 8)
			{
			return true;
		}else 
		return false;
	}
	
	short getFila()  
	{
		return fila;
	}
	
	short getColumna() 
	{
		return columna;
	}
	
	void setFila(short f) 
	{
		fila = f;
	}
	
	void setColumna(short c) 
	{
		columna = c;
	}
};

enum Direccion 
{
	N, NE, NO, O, E, S, SE, SO
};
string direccionP(Direccion dir) 
{
	switch (dir) 
	{
	case N: return "Norte";
	case NE: return "NorEste";
	case NO: return "NorOeste";
	case O: return "Oeste";
	case E: return "Este";
	case S: return "Sur";
	case SE: return "SurEste";
	case SO: return "SurOeste";
	default: return "No valido";
	}
}


class Peon : public Pieza 
{
private:
	Direccion direccion;
	short cuadros;
public:
	Peon()
	{
		Pieza();
		direccion = S; 
		cuadros =1;
	}
	
	Peon(short f, short c, Direccion dir, short cuad = 1) 
	{
		Pieza(f, c);
		direccion = dir;
		cuadros = cuad;
	}
	void verInfo()
	{
		cout<<"Direccion: "<<direccionP(direccion)<<"  Cuadros: "<<cuadros<<endl;
	}
	void avanzar()
	{
		short nuevaFila = getFila();
		short nuevaColumna = getColumna();
		
		switch(direccion) 
		{
		case N: nuevaFila += cuadros; 
		break;
		case S: nuevaFila -= cuadros; 
		break;
		case E: nuevaColumna += cuadros;
		break;
		case O: nuevaColumna -= cuadros; 
		break;
		case NE: 
		{
			nuevaFila += cuadros; 
			nuevaColumna += cuadros;
			break; 
		}
		case NO:
		{
			nuevaFila += cuadros; 
			nuevaColumna -= cuadros; 
			break; 
		}
		case SE:
		{ nuevaFila -= cuadros;
		nuevaColumna += cuadros;
		break; 
		}
		case SO: 
		{ nuevaFila -= cuadros; 
		nuevaColumna -= cuadros;
		break; 
		}
		}
		
		if (esValido(nuevaFila, nuevaColumna))
		{
			setFila(nuevaFila);
			setColumna(nuevaColumna);
			cout<<"El peon avanzado a "<<nuevaFila<<" "<<nuevaColumna<<" "<<endl;
		} else {
			cout<<"No valido"<<endl;
		}
	}

	bool puedoIrA(short f, short c) 
	{
		short expectedFila = getFila();
		short expectedColumna = getColumna();
		
		switch(direccion) 
		{
		case N: expectedFila += cuadros;
		break;
		case S: expectedFila -= cuadros;
		break;
		case E: expectedColumna += cuadros;
		break;
		case O: expectedColumna -= cuadros;
		break;
		case NE: { 
			expectedFila += cuadros;
			expectedColumna += cuadros;
			break;
		}
		case NO: { expectedFila += cuadros; 
		expectedColumna -= cuadros;
		break; 
		}
		case SE: { expectedFila -= cuadros;
		expectedColumna += cuadros;
		break;
		}
		case SO: { expectedFila -= cuadros;
		expectedColumna -= cuadros;
		break; 
		}
		}
		return (f == expectedFila && c == expectedColumna) && esValido(f, c);
	}
};

class Torre : public Pieza 
{
private:
	Direccion direccion;
	short cuadros;
	
public:
	Torre() 
	{
		Pieza();
		direccion = E;
		cuadros = 8;
	}
	
	Torre(short f, short c, Direccion dir, short cuad = 8)
	{
		Pieza(f, c);
		direccion = dir;
		cuadros = cuad;
	}

	void verInfo()
	{
		cout<<"Direccion: "<<direccionP(direccion)<<"  Cuadros: "<<cuadros<<endl;
	}
	
	void mover()
	{
		short nuevaFila = getFila();
		short nuevaColumna = getColumna();
		
		switch(direccion)
		{
		case N: nuevaFila += cuadros; 
		break;
		case S: nuevaFila -= cuadros;
		break;
		case E: nuevaColumna += cuadros; 
		break;
		case O: nuevaColumna -= cuadros; 
		break;
		case NE: { nuevaFila += cuadros;
		nuevaColumna += cuadros;
		break; 
		}
		case NO: { nuevaFila += cuadros; 
		nuevaColumna -= cuadros;
		break;
		}
		case SE: { nuevaFila -= cuadros; 
		nuevaColumna += cuadros; 
		break; 
		}
		case SO: { nuevaFila -= cuadros; 
		nuevaColumna -= cuadros; 
		break;
		}
		}
		
		if (esValido(nuevaFila, nuevaColumna)) 
		{
			setFila(nuevaFila);
			setColumna(nuevaColumna);
			cout<<"Torre se ha movido a"<<nuevaFila<<"  "<<nuevaColumna<<"  "<<endl;
		} else {
			cout<<"No valido"<<endl;
		}
	}
	
	bool puedoIrA(short f, short c) 
	{
		switch(direccion) 
		{
		case N:
		case S:
		case E:
		case O:
			return (f == getFila() || c == getColumna()) && esValido(f, c);
		case NE:
		case NO:
		case SE:
		case SO:
			return (abs(f - getFila()) == abs(c - getColumna())) && esValido(f, c);
		default:
			return false;
		}
	}
};

class Tablero 
{
private:
	Pieza* piezas[32];
	int contador;
	
public:
	Tablero() 
	{
		contador = 0;
	}
	
	void agregarPieza(Pieza* p) 
	{
		if (contador < 32) 
		{
			piezas[contador++] = p;
			cout<<"Pieza agregada"<<endl;
		} else {
			cout<<"El tablero esta lleno"<<endl;
		}
	}
	
};

int main() {
	Peon peon1(2, 2, N, 1);
	peon1.verInfo();
	peon1.avanzar();
	
	Torre torre1(1, 1, E, 8);
	torre1.verInfo();
	torre1.mover();
	
	return 0;
}

