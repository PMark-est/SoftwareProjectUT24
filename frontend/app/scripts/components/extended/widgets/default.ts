/** @format */
import { html } from "@/util";
import { Widget, WidgetScope } from "./common";

type DefaultWidgetScope = WidgetScope & {
    case: "sensitive" | "insensitive";
    makeSensitive: () => void;
    makeInsensitive: () => void;
    options: Array<{ value: string; label: string }>;
    selectedOption: string;
};

export const defaultWidget: Widget = {
    template: ({ placeholder }) => html`
        <select
            ng-model="selectedOption"
            class="arg_value"
            escaper
            ng-model-options='{debounce : {default : 300, blur : 0}, updateOn: "default blur"}'
            ng-options="option.value as option.label for option in options"
        >
            <option value="" disabled hidden>${placeholder}</option>
        </select>

        <span uib-dropdown>
            <span
                ng-class='{sensitive : case == "sensitive", insensitive : case == "insensitive"}'
                class="val_mod"
                uib-dropdown-toggle
            >
                Aa
            </span>
            <ul class="mod_menu" uib-dropdown-menu>
                <li><a ng-click="makeSensitive()">{{'case_sensitive' | loc:$root.lang}}</a></li>
                <li><a ng-click="makeInsensitive()">{{'case_insensitive' | loc:$root.lang}}</a></li>
            </ul>
        </span>
    `,
    controller: [
        "$scope",
        "$http",
        function ($scope: DefaultWidgetScope, $http) {
            // Initialize case sensitivity based on $scope.orObj.flags
            if ($scope.orObj.flags && $scope.orObj.flags.c) {
                $scope.case = "insensitive";
            } else {
                $scope.case = "sensitive";
            }

            // Define methods for toggling case sensitivity
            $scope.makeSensitive = function () {
                $scope.case = "sensitive";
                if ($scope.orObj.flags) {
                    delete $scope.orObj.flags["c"];
                }
            };

            $scope.makeInsensitive = function () {
                const flags = $scope.orObj.flags || {};
                flags["c"] = true;
                $scope.orObj.flags = flags;

                $scope.case = "insensitive";
            };

            // Initialize options as an empty array
            $scope.options = [];

            // Fetch options dynamically based on positional attribute
            const fetchOptions = (positionalAttribute = "case") => {
                $http.get(`http://andmebaas.zapto.org:8080/lexicon?positional_attribute=${positionalAttribute}`)
                    .then((response) => {
                        // Assuming the options come in an array format under "Arguments" key
                        $scope.options = response.data.Arguments.map((arg: string) => ({
                            value: arg,
                            label: arg === "__UNDEF__" ? "Undefined" : arg // Label customization
                        }));
                    })
                    .catch((error) => {
                        console.error("Error fetching options:", error);
                        // Optional: Display an error message in options
                        $scope.options = [{ value: "", label: "Error loading options" }];
                    });
            };

            // Call fetchOptions initially
            fetchOptions(); // You can modify to accept a positional attribute if needed
        },
    ],
};

