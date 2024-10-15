/** @format */
import angular from "angular"
import { html } from "@/util"

export default angular.module("korpApp").component("mycomp", {
    template: html`<span class="pl-4">
        Filter:
        <uib-dropdown>
            <button uib-dropdown-toggle type="button">{{$ctrl.selected}}<span class="caret"></span></button>
            <ul uib-dropdown-menu>
                <li ng-repeat="item in $ctrl.types">
                    <a href="" ng-click="$ctrl.selectItem(item)">{{item}}</a>
                </li>
            </ul>
        </uib-dropdown>
    </span>`,
    bindings: {
        kwicHits: "=",
    },
    controller: [
        "$timeout",
        /**
         * @param {import("angular").ITimeoutService} $timeout
         */
        function ($timeout) {
            let $ctrl: any = this
            $ctrl.selected = "Dropdown"
            let types = new Set()

            $ctrl.selectItem = function (item) {
                console.log("nupp vajutatud!!!")
                $ctrl.selected = item
            }

            $ctrl.$onChanges = (changes) => {
                $timeout(() => {
                    if ($ctrl.kwicHits === undefined) return
                    $ctrl.kwicHits.forEach((element) => {
                        if (element.match === undefined) return
                        element.tokens.forEach((token) => {
                            if (token.error_type === undefined || token.error_type === "_") return
                            types.add(token.error_type)
                        })
                    })
                    $ctrl.types = Array.from(types)
                    console.log($ctrl.types)
                }, 1000)
            }
        },
    ],
})
