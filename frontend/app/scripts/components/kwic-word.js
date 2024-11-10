/** @format */
import angular from "angular"
import { html } from "@/util"

angular.module("korpApp").component("kwicWord", {
    template: html`
        <div id="sentence_root">
        <span ng-repeat="word in $ctrl.left" class="left">
            <!-- Check if 'word' is a phrase or a single word -->
            <span ng-if="!word.phrase" class="word" ng-class="$ctrl.getClass(word)">
                {{ word.word }}
                <span ng-if="word.error_correction != '_'" class="tooltip"> {{ word.error_correction }} </span>
            </span>

            <span ng-if="word.phrase" class="phrase" ng-class="$ctrl.getClass(word)">
                <span ng-repeat="phraseWord in word.phrase.tokens" class="word word_in_phrase">
                    {{ phraseWord.word }}
                    <span ng-if="phraseWord.error_correction != '_'" class="tooltip"> {{ phraseWord.error_correction }} </span>
                </span>
                <span ng-if="word.error.error_correction != '_'" class="tooltip"> {{ word.error.error_correction }} </span>
            </span>
        </span>

        <span ng-if="$ctrl.phrase.length != 0" class="phrase" ng-class="$ctrl.getClass($ctrl.phrase)">
            <span ng-repeat="word in $ctrl.phrase_left" class="word word_in_phrase left" ng-class="$ctrl.getClass(word)">
                {{word.word}}
                <span ng-if="word.error_correction != '_'" class="tooltip"> {{ word.error_correction }} </span>
            </span>
            <span ng-repeat="word in $ctrl.word" class="word word_in_phrase match">
                {{word.word}}
                <span ng-if="word.error_correction != '_'" class="tooltip"> {{ word.error_correction }} </span>
            </span>
            <span ng-repeat="word in $ctrl.phrase_right" class="word word_in_phrase right" ng-class="$ctrl.getClass(word)">
                {{word.word}}
                <span ng-if="word.error_correction != '_'" class="tooltip"> {{ word.error_correction }} </span>
            </span>
            <span ng-if="$ctrl.phrase.error.error_correction != '_'" class="tooltip"> {{ $ctrl.phrase.error.error_correction }} </span>
        </span>
        <span ng-if="$ctrl.phrase.length == 0" ng-repeat="word in $ctrl.word" class="word match">
            {{word.word}}
            <span ng-if="word.error_correction != '_'" class="tooltip"> {{ word.error_correction }} </span>
        </span>

        <span ng-repeat="word in $ctrl.right" class="right">
            <!-- Check if 'word' is a phrase or a single word -->
            <span ng-if="!word.phrase" class="word" ng-class="$ctrl.getClass(word)">
                {{ word.word }}
                <span ng-if="word.error_correction != '_'" class="tooltip"> {{ word.error_correction }} </span>
            </span>

            <span ng-if="word.phrase" class="phrase" ng-class="$ctrl.getClass(word)">
                <span ng-repeat="phraseWord in word.phrase.tokens" class="word word_in_phrase">
                    {{ phraseWord.word }}
                    <span ng-if="phraseWord.error_correction != '_'" class="tooltip"> {{ phraseWord.error_correction }} </span>
                </span>
                <span ng-if="word.error.error_correction != '_'" class="tooltip"> {{ word.error.error_correction }} </span>
            </span>
        </span>
        </div>
    `,
    bindings: {
        word: "<",
        sentence: "<",
        sentenceIndex: "<",
    },
    controller: [
        "$scope", "$element", "$window", "popupService",
        function ($scope, $element, $window, popupService) {
            let tooltipsVisible = false

            this.$onInit = () => {
                // Add incoming values to local scope, to be used by click handlers in the Kwic component.
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
                    //console.log(token)
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

            function showTooltips() {
                if (tooltipsVisible) return
                tooltipsVisible = true

                const tooltipElements = $element[0].querySelectorAll(".tooltip")
                if(tooltipElements.length == 0) return

                const root = $element[0].querySelector("#sentence_root")
                root.style.marginTop = "30px"

                tooltipElements.forEach(obj => {
                    obj.style.display = "block"
                    const wordElement = obj.parentElement
                    const tableElement = $(".table_scrollarea")[0]
                    const tableRect = tableElement.getBoundingClientRect()
                    const wordRect = wordElement.getBoundingClientRect()
                    const tooltipRect = obj.getBoundingClientRect()
                    const topOffset = wordElement.classList.contains("word_in_phrase") ? 60 : 30
                    obj.style.top = wordRect.top - tableRect.top - topOffset + "px"
                    wordElement.style.width = Math.max(tooltipRect.width, wordRect.width) + "px"
                })
            }

            function hideTooltips() {
                if (!tooltipsVisible) return
                tooltipsVisible = false

                const tooltipElements = $element[0].querySelectorAll(".tooltip")
                if(tooltipElements.length == 0) return

                const root = $element[0].querySelector("#sentence_root")
                root.style.marginTop = "0px"

                tooltipElements.forEach(obj => {
                    obj.style.display = "none"
                    const wordElement = obj.parentElement
                    wordElement.style.width = "fit-content"
                })
            }

            popupService.onShowPopups($scope, function (sentIndex) {
                if(sentIndex == $scope.sentenceIndex) {
                    showTooltips()
                }
                else {
                    hideTooltips()
                }
            });

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
