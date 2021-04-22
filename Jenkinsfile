pipeline {
	agent any

	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
	}

	parameters {
		booleanParam name: 'EJECUTA_COMPROBACIONES', defaultValue: true, description: '¿Hago Pruebas?'
		//booleanParam name: 'ANALISIS_ESTATICO', defaultValue: true, description: '¿Analizo el codigo?'
		//booleanParam name: 'INSTALA', defaultValue: true, description: '¿Instalo los artefactos?'
	}

	stages {
        stage('Construye') {
            steps {
                cmake arguments: '', installation: 'InSearchPath'
                cmakeBuild buildType: 'Release', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true]]
            }
        }

        stage('Prueba') {
            when {
                environment name: 'EJECUTA_COMPROBACIONES', value: 'true'
            }
            steps {
                //ctest 'InSearchPath'
                sh label: 'GuionGoogleTest', returnStatus: true, script: './proyecto/pruebas --gtest_output=xml:"./proyecto/resultado.xml"'
                
            }
        }

        //stage('Analiza') {
        //    when {
        //        environment name: 'ANALISIS_ESTATICO', value: 'true'
        //    }
        //    steps {
        //        sh label: '', returnStatus: true, script: 'cppcheck . --xml --language=c++ --suppressions-list=suppressions.txt 2> cppcheck-result.xml'
        //        publishCppcheck allowNoReport: true, ignoreBlankFiles: true, pattern: '**/cppcheck-result.xml'
        //    }
        //}

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

    post {
        success {
            junit testResults: './proyecto/resultado.xml', allowEmptyResults: false
        }
    }
}