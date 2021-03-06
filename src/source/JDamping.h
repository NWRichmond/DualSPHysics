//HEAD_DSPH
/*
 <DUALSPHYSICS>  Copyright (c) 2018 by Dr Jose M. Dominguez et al. (see http://dual.sphysics.org/index.php/developers/). 

 EPHYSLAB Environmental Physics Laboratory, Universidade de Vigo, Ourense, Spain.
 School of Mechanical, Aerospace and Civil Engineering, University of Manchester, Manchester, U.K.

 This file is part of DualSPHysics. 

 DualSPHysics is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License 
 as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
 
 DualSPHysics is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details. 

 You should have received a copy of the GNU Lesser General Public License along with DualSPHysics. If not, see <http://www.gnu.org/licenses/>. 
*/

//:#############################################################################
//:# Cambios:
//:# =========
//:# - Clase para gestionar zonas de amortiguamiento. (13-01-2014)
//:# - Modificacion para usar la funcion exponencial de S.J. Lind et al. 2012. (02-09-2014)
//:# - Muestra vector normal del plano para facilitar su comprension. (26-11-2014)
//:# - Se puede aplicar un factor de amortiguacion para cada componente. (26-11-2014)
//:# - Documentacion del codigo en ingles. (08-08-2017)
//:#############################################################################

/// \file JDamping.h \brief Declares the class \ref JDamping.

#ifndef _JDamping_
#define _JDamping_

#include <string>
#include <vector>
#include "JObject.h"
#include "Types.h"

class JXml;
class TiXmlElement;
class JLog2;

//##############################################################################
//# XML format in _FmtXML_Damping.xml.
//##############################################################################

//##############################################################################
//# JDamping
//##############################################################################
/// \brief Manages the info of damping zones.

class JDamping : protected JObject
{
public:
/// Structure with damping information.
  typedef struct {
    tdouble3 limitmin;  ///<Minimal reduction position. | Posicion de reduccion minima.
    tdouble3 limitmax;  ///<Miximum reduction position. | Posicion de reduccion maxima.
    float overlimit;    ///<Distance after limit with maximum reduction. | Distancia despues de limite con reduccion maxima.
    float redumax;      ///<Percentage of maximum reduction. | Porcentaje de reduccion maxima.
    tfloat3 factorxyz;  ///<Factor applied on each axis. | Factor de aplicacion en cada eje.
    bool usedomain;     ///<Indicates use of domain planes. | Indica uso de planos del dominio.
    double domzmin;     ///<Domain definition - Z minimum. | Definicion de dominio - Z minima.
    double domzmax;     ///<Domain definition - Z maximum. | Definicion de dominio - Z maxima.
    tdouble4 dompla0;   ///<Domain definition - plane 0.
    tdouble4 dompla1;   ///<Domain definition - plane 1.
    tdouble4 dompla2;   ///<Domain definition - plane 2.
    tdouble4 dompla3;   ///<Domain definition - plane 3.
    tdouble4 plane;     ///<Plane at the limitmin point. | Plano en el punto limitmin.
    float dist;         ///<Distance between limitmin and limitmax points. | Distancia entre puntos limitmin y limitmax.
  }StDamping;

private:
  JLog2* Log;
  std::vector<StDamping> List;

  void ReadXml(JXml *sxml,TiXmlElement* ele);
  void ComputeDamping(const JDamping::StDamping &da,double dt,unsigned n,unsigned pini,const tdouble3 *pos,const typecode *code,tfloat4 *velrhop)const;
  void ComputeDampingPla(const JDamping::StDamping &da,double dt,unsigned n,unsigned pini,const tdouble3 *pos,const typecode *code,tfloat4 *velrhop)const;

public:
  JDamping(JLog2* log);
  ~JDamping();
  void Reset();

  void LoadXml(JXml *sxml,const std::string &place);
  void VisuConfig(std::string txhead,std::string txfoot);

  unsigned GetCount()const{ return(unsigned(List.size())); }
  const JDamping::StDamping* GetDampingZone(unsigned c)const;

  void ComputeDamping(double timestep,double dt,unsigned n,unsigned pini,const tdouble3 *pos,const typecode *code,tfloat4 *velrhop)const;
  void ComputeDamping(double timestep,double dt,unsigned n,unsigned pini,const tdouble3 *pos,tfloat4 *velrhop)const{ ComputeDamping(timestep,dt,n,pini,pos,NULL,velrhop); }
};


#endif


