/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

pipeline {
	agent any

	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
        timeout(time: 30, unit: 'SECONDS')
	}

	parameters {
		booleanParam name: 'EJECUTA_COMPROBACIONES', defaultValue: true, description: '¿Hago Pruebas?'
		booleanParam name: 'ANALISIS_ESTATICO', defaultValue: true, description: '¿Analizo el codigo?'
		//booleanParam name: 'INSTALA', defaultValue: true, description: '¿Instalo los artefactos?'
	}

	stages {
        stage('Construye') {
            steps {
                sh label: 'ConstruyeObra', script: 'rm -rf obra'
                sh label: 'ConstruyeObra', script: 'mkdir obra'
                sh label: 'EjecutaCMake', script: 'cmake CXXFLAGS="-ggdb3" -S . -B obra'
                sh label: 'EjecutaCMakeBuild', script: 'cmake --build obra --parallel=$(nproc)'
            }
        }

        stage('Analiza') {
            when {
                environment name: 'ANALISIS_ESTATICO', value: 'true'
            }
            steps {
                sh label: '', returnStatus: true, script: 'echo "{nat a; apaga();}" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v proyecto/compilador'
            }
        }

        stage('Prueba') {
            when {
                environment name: 'EJECUTA_COMPROBACIONES', value: 'true'
            }
            steps {
                //ctest 'InSearchPath'
                sh label: 'EjecutaGoogleTest', script: 'proyecto/pruebas --gtest_output=xml:resultado.xml'
                
            }
            post {
                always {
                    junit testResults: 'resultado.xml', allowEmptyResults: false
                }
            }
        }

        //stage('Instala') {
        //    when {
        //        environment name: 'INSTALA', value: 'true'
        //    }
        //    steps {
        //        sh label: '', returnStatus: true, script: '''cp jenkinsexample ~
        //        cp test/testPro ~'''
        //    }
        //}
	}
}