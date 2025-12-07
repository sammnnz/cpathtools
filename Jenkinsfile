pipeline {
    agent {
        label "jcasc-agent-1"
    }
    
    options {
        timeout(time: 30, unit: 'MINUTES')
        buildDiscarder(logRotator(numToKeepStr: '10'))
    }
    
    triggers {
        githubPush()
        // Срабатывает при пуше в GitHub
        // pollSCM('H/5 * * * *')
    }
    
    stages {
        stage('Install Dependencies') {
            steps {
                sh '''
                    sudo apt update
                    sudo apt install check -y
                '''
            }
            post {
                success {
                    echo '✅ Установка зависимотей успешна!'
                }
                failure {
                    echo '❌ Ошибка установки зависимостей!'
                }
            }
        }
        stage('Checkout') {
            steps {
                echo '📥 Получаем код из GitHub...'
                // checkout scm
                git branch: 'main',
                    credentialsId: 'b9c7e4b7-8379-419f-9e62-fcd30ae92374',
                    poll: false,
                    url: 'git@github.com:sammnnz/cpathtools.git'
            }
        }
        
        stage('Explore Project') {
            steps {
                sh '''
                    echo "=== Смотрим что в репозитории ==="
                    pwd
                    ls -lrta
                '''
            }
        }
        
        stage('Setup Environment') {
            steps {
                echo '🔧 Проверяем окружение...'
                sh 'gcc --version'
                sh 'make --version'
            }
        }
        
        stage('Compile') {
            steps {
                echo '🏗️ Компилируем проект...'
                sh 'make build'
                sh 'make test'
            }
            post {
                success {
                    echo '✅ Компиляция успешна!'
                }
                failure {
                    echo '❌ Ошибка компиляции!'
                }
            }
        }
        
        stage('Run Tests') {
            steps {
                echo '🧪 Запускаем тесты...'
                sh '''
                    ./tests/check_cpathtools
                '''
            }
            environment {
                LD_LIBRARY_PATH = sh(script: 'pwd', returnStdout: true).trim()
            }
            post {
                always {
                    // Сохраняем результаты покрытия
                    echo ""
                }
            }
        }
        
        stage('Static Analysis') {
            steps {
                echo '🔍 Проверяем код...'
                sh '''
                    echo "Проверка на warnings..."
                    make clean
                '''
            }
        }
    }
    
    post {
        always {
            echo '🎉 Pipeline завершен!'
            cleanWs()  // Очищаем workspace
        }
        success {
            emailext (
                subject: "SUCCESS: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
                body: "Проект ${env.JOB_NAME} собран успешно!\nСмотри: ${env.BUILD_URL}"
            )
        }
        failure {
            emailext (
                subject: "FAILED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
                body: "Сборка ${env.JOB_NAME} упала!\nСмотри: ${env.BUILD_URL}"
            )
        }
    }
}
