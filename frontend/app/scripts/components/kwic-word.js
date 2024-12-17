/** @format */
import angular from "angular"
import { html } from "@/util"

angular.module("korpApp").component("kwicWord", {
    template: html`
        <span id="sentence_root">
            <span ng-if="!$ctrl.word.word" class="phrase" ng-class="$ctrl.getClass($ctrl.word)">
                    <span ng-if="word.error" class="tooltip"> {{word.error.error_correction}} </span>
                    <span style="display:flex;gap:4px;">
                        <span ng-repeat="phraseWord in $ctrl.word.phrase_tokens" ng-class="$ctrl.getClass(phraseWord)">
                            <span ng-if="phraseWord.error_correction !== '_'" class="tooltip"> {{phraseWord.error_correction}} </span>
                            <span class="word" ng-if"phraseWord.word" ng-class="$ctrl.getClass(phraseWord)">{{phraseWord.word}}</span>
                            <span ng-if="!phraseWord.word" class="phrase" ng-class="$ctrl.getClass(phraseWord)">
                                <span ng-if="phraseWord.error" class="tooltip"> {{phraseWord.error.error_correction}} </span>
                                <span>
                                    <kwic-word
                                    ng-repeat="nestedPhraseWord in phraseWord.phrase_tokens"
                                    word="nestedPhraseWord"
                                    sentence="$ctrl.sentence"
                                    sentence-index="$ctrl.sentenceIndex"
                                    />
                                </span>
                            </span>
                        </span>
                    </span>
                </span>
            </span>
            <span ng-if="$ctrl.word.word" class="word" ng-class="$ctrl.getClass($ctrl.word)">
                <span ng-if="$ctrl.word.error_correction != '_'" class="tooltip">
                    {{ $ctrl.word.error_correction }}
                </span>
                {{::$ctrl.word.word}}
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
        "$element",
        "$window",
        "popupService",
        function ($scope, $element, $window, popupService) {
            let tooltipsVisible = false
            this.$onInit = () => {
                // Add incoming values to local scope, to be used by click handlers in the Kwic component.
                $scope.word = this.word
                //console.log(this.sentence)
                $scope.sentence = this.sentence
                $scope.sentenceIndex = this.sentenceIndex
            }

            function showTooltips() {
                if (tooltipsVisible) return
                tooltipsVisible = true
                let tooltipElements
                if (
                    $scope.sentence.match.phrase &&
                    $scope.word.word_id >= $scope.sentence.tokens[$scope.sentence.match.phrase].phrase.tokens[0].word_id
                ) {
                    tooltipElements = $element[0].parentElement.parentElement.parentElement.querySelectorAll(".tooltip")
                } else {
                    tooltipElements = $element[0].querySelectorAll(".tooltip")
                }
                if (tooltipElements.length == 0) return
                tooltipElements.forEach((obj) => {
                    obj.style.display = "block"
                })
            }
            function hideTooltips() {
                if (!tooltipsVisible) return
                tooltipsVisible = false
                const tooltipElements = $element[0].querySelectorAll(".tooltip")
                if (tooltipElements.length == 0) return
                tooltipElements.forEach((obj) => {
                    obj.style.display = "none"
                })
            }
            popupService.onShowPopups($scope, function (sentIndex) {
                if (sentIndex == $scope.sentenceIndex) {
                    showTooltips()
                } else {
                    hideTooltips()
                }
            })

            /** Produce applicable class names depending on token data. */
            this.getClass = function (word) {
                let errorType = ["_"]
                if (word.word) {
                    errorType = word.error_type
                } else {
                    errorType = word.error.error_type
                }
                let classes = []
                classes.push({
                    reading_match: this.word._match,
                    punct: this.word._punct,
                    match_sentence: this.word._matchSentence,
                    link_selected: this.word._link_selected,
                    open_sentence: "_open_sentence" in this.word,
                    has_error: this.word.error_tag && this.word.error_tag != "_",
                })
                if (word !== undefined) {
                    if (this.sentence.match.start_id === word.word_id) classes = classes.concat("match")
                }
                //console.log(classes)
                classes = classes.concat(errorType)
                return classes
            }
        },
    ],
})
