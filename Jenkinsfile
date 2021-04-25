pipeline {
	agent any

	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
        timeout(time: 120, unit: 'SECONDS')
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
                sh label: 'EjecutaCMake', script: 'cmake CXXFLAGS="-g" -S . -B obra'
                sh label: 'EjecutaCMakeBuild', script: 'cmake --build obra --parallel=$(nproc)'
            }
        }

        stage('Analiza') {
            when {
                environment name: 'ANALISIS_ESTATICO', value: 'true'
            }
            steps {
                sh label: '', returnStatus: true, script: 'ls proyecto'
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