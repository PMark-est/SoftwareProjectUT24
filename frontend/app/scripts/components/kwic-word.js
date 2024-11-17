/** @format */
import angular from "angular"
import { html } from "@/util"

angular.module("korpApp").component("kwicWord", {
    template: html`
        <span id="sentence_root">
            <span ng-if="!$ctrl.word.word" class="phrase" ng-class="$ctrl.getClass(undefined, undefined)">
                <span
                    ng-repeat="phraseWord in $ctrl.word.phrase.tokens"
                    class="word"
                    ng-class="$ctrl.getClass(phraseWord, $ctrl.sentence.match.phrase)"
                >
                    {{phraseWord.word}}
                </span>
                <span ng-if="word.error" class="tooltip"> {{word.error.error_correction}} </span>
            </span>
            <span ng-if="$ctrl.word.word" class="word" ng-class="$ctrl.getClass(undefined, undefined)">
                {{::$ctrl.word.word}}
                <span ng-if="$ctrl.word.error_correction != '_'" class="tooltip">
                    {{ $ctrl.word.error_correction }}
                </span>
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
                const tooltipElements = $element[0].querySelectorAll(".tooltip")
                if (tooltipElements.length == 0) return
                const root = $element[0].querySelector("#sentence_root")
                root.style.marginTop = "30px"
                tooltipElements.forEach((obj) => {
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
                if (tooltipElements.length == 0) return
                const root = $element[0].querySelector("#sentence_root")
                root.style.marginTop = "0px"
                tooltipElements.forEach((obj) => {
                    obj.style.display = "none"
                    const wordElement = obj.parentElement
                    wordElement.style.width = "fit-content"
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
            this.getClass = function (word, matchInPhrase) {
                let errorType = ["_"]
                if (this.word.word) {
                    errorType = this.word.error_type
                } else {
                    errorType = this.word.error.error_type
                    //console.log($element[0].parentElement.parentElement.querySelectorAll(".tooltip"))
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
                if (matchInPhrase && Number(word.word_id) === this.sentence.match.start + 1) {
                    classes.push({
                        match: word,
                    })
                }
                classes = classes.concat(errorType)
                //console.log(classes)
                return classes
            }
        },
    ],
})
