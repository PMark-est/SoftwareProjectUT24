/** @format */
import angular from "angular"
import { html } from "@/util"

/*

<span ng-if="$ctrl.word.phrase === undefined" class="word" ng-class="$ctrl.getClass()">
            {{::$ctrl.word.word}}
        </span>
        <span ng-if="$ctrl.word.phrase !== undefined" class="phrase" ng-class="$ctrl.getClass()">
            <span ng-repeat="word in $ctrl.word.phrase.tokens" class="word"> {{word.word}} </span>
        </span>

*/

angular.module("korpApp").component("kwicWord", {
    template: html`
        <span ng-repeat="word in $ctrl.left" class="left">
            <!-- Check if 'word' is a phrase or a single word -->
            <span ng-if="!word.phrase" class="word" ng-class="$ctrl.getClass(word)"> {{ word.word }} </span>

            <span ng-if="word.phrase" class="phrase" ng-class="$ctrl.getClass(word)">
                <span ng-repeat="phraseWord in word.phrase.tokens" class="word"> {{ phraseWord.word }} </span>
            </span>
        </span>

        <span ng-if="$ctrl.phrase != []" class="phrase" ng-class="$ctrl.getClass($ctrl.phrase)">
            <span ng-repeat="word in $ctrl.phrase_left" class="word left" ng-class="$ctrl.getClass(word)"
                >{{word.word}}
            </span>
            <span ng-repeat="word in $ctrl.word" class="word match">{{word.word}} </span>
            <span ng-repeat="word in $ctrl.phrase_right" class="word right" ng-class="$ctrl.getClass(word)"
                >{{word.word}}
            </span>
        </span>
        <span ng-if="$ctrl.phrase == []" ng-repeat="word in $ctrl.word" class="word match">{{word.word}} </span>

        <span ng-repeat="word in $ctrl.right" class="right">
            <!-- Check if 'word' is a phrase or a single word -->
            <span ng-if="!word.phrase" class="word" ng-class="$ctrl.getClass(word)"> {{ word.word }} </span>

            <span ng-if="word.phrase" class="phrase" ng-class="$ctrl.getClass(word)">
                <span ng-repeat="phraseWord in word.phrase.tokens" class="word"> {{ phraseWord.word }} </span>
            </span>
        </span>
    `,
    bindings: {
        word: "<",
        sentence: "<",
        sentenceIndex: "<",
    },
    controller: [
        "$scope",
        function ($scope) {
            this.$onInit = () => {
                // Add incoming values to local scope, to be used by click handlers in the Kwic component.
                $scope.word = this.word
                $scope.sentence = this.sentence
                $scope.sentenceIndex = this.sentenceIndex
                //console.log(this.sentence)
                this.left = []
                this.right = []
                this.phrase_left = []
                this.phrase_right = []
                this.phrase = []
                this.word = []
                let matchSeen = false
                for (let index = 0; index < this.sentence.tokens.length; index++) {
                    const token = this.sentence.tokens[index]
                    const isMatchPhrase = token.word === undefined && index === this.sentence.match.phrase
                    if (isMatchPhrase) {
                        this.phrase = token
                        this.phrase_left = this.phrase_left.concat(
                            token.phrase.tokens.slice(0, this.sentence.match.start - this.sentence.match.phrase - 1)
                        )
                        //console.log("vaata siia munn")
                        matchSeen = true
                        this.word = [token.phrase.tokens[this.sentence.match.start - this.sentence.match.phrase - 1]]
                        this.phrase_right = this.phrase_right.concat(
                            token.phrase.tokens.slice(
                                this.sentence.match.start - this.sentence.match.phrase,
                                token.phrase.tokens.length
                            )
                        )
                    } else {
                        if (index === this.sentence.match.start) {
                            matchSeen = true
                            this.word = [token]
                        } else if (matchSeen) {
                            this.right.push(token)
                        } else {
                            this.left.push(token)
                        }
                    }
                }
                /*console.log(this.left)
                console.log(this.right)
                console.log(this.phrase_left)
                console.log(this.phrase_right)
                console.log(this.word)
                /*if (this.phraseMatch) {
                    const length = this.sentence.tokens[this.sentence.match.phrase].phrase.tokens.length
                    this.left = this.sentence.tokens[this.sentence.match.phrase].phrase.tokens
                        .slice(0, this.sentence.match.start - this.sentence.match.phrase - 1)
                        .map((elem) => elem.word)
                    this.right = this.sentence.tokens[this.sentence.match.phrase].phrase.tokens
                        .slice(this.sentence.match.start - this.sentence.match.phrase, length)
                        .map((elem) => elem.word)
                }*/
            }

            /** Produce applicable class names depending on token data. */
            this.getClass = function (word) {
                let errorType = ["_"]
                let errorTag = ["_"]
                if (word.length > 1) word = word[0]
                if (word.phrase !== undefined) {
                    errorType = word.error.error_type.split("|")
                } else if (word.error_type) {
                    errorType = word.error_type.split("|")
                }
                let classes = []
                classes.push({
                    reading_match: word._match,
                    punct: word._punct,
                    match_sentence: word._matchSentence,
                    link_selected: word._link_selected,
                    open_sentence: "_open_sentence" in word,
                    has_error: word.error_tag && word.error_tag != "_",
                })
                classes = classes.concat(errorType)
                //console.log(classes)
                return classes
            }
        },
    ],
})
